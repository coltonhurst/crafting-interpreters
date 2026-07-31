use std::env;
use std::fs;
use std::io;
use std::io::Write;
use std::path::Path;
use std::process;

mod token;
mod token_type;

// Exit codes from sysexits.h
// https://www.man7.org/linux/man-pages/man3/sysexits.h.3head.html
const EXIT_CODE_SUCCESS: i32 = 0;
const EXIT_CODE_INCORRECT_USAGE: i32 = 64;
const EXIT_CODE_FORMAT_ERROR: i32 = 65;

// Stores if there was an error
static mut HAD_ERROR: bool = false;

// The main entry point for rlox
fn main() {
    // Get args passed to rlox
    let mut args: Vec<String> = env::args().collect();

    // Remove first arg because the first item in std::env::args()
    // is the executable path
    args.remove(0);

    // Handle args
    if args.len() > 1 {
        println!("Usage: rlox [script]");
        process::exit(EXIT_CODE_INCORRECT_USAGE);
    } else if args.len() == 1 {
        let source_path = Path::new(&args[0]);
        let result = run_file(source_path);

        if let Err(e) = result {
            eprintln!("Error: There was an issue reading the file\n{:?}", e);
        }
    } else {
        run_prompt();
    }

    // Exit successfully
    process::exit(EXIT_CODE_SUCCESS)
}

// Reads a file into a string and runs it
fn run_file(p: &Path) -> Result<(), io::Error> {
    let f = fs::read_to_string(p)?;
    run(f);

    unsafe {
        if HAD_ERROR {
            process::exit(EXIT_CODE_FORMAT_ERROR);
        }
    }

    Ok(())
}

// Starts a rlox REPL, running one line at a time
fn run_prompt() {
    let stdin = io::stdin();
    let mut stdout = io::stdout();

    loop {
        print!("> ");
        _ = stdout.flush();

        let mut input = String::new();
        match stdin.read_line(&mut input) {
            Ok(0) => {
                println!("\nExiting via Ctrl-D");
                break;
            }
            Ok(_) => {
                run(input);

                unsafe {
                    HAD_ERROR = false;
                }
            }
            Err(e) => {
                println!("\nError: {:?}", e);
                break;
            }
        }
    }
}

// Runs source code
fn run(source: String) {
    let tokens = source.split_whitespace();

    for token in tokens {
        println!("{:?}", token);
    }
}

#[allow(dead_code)]
fn error(line: i32, message: String) {
    report(line, String::new(), message);
}

#[allow(dead_code)]
fn report(line: i32, location: String, message: String) {
    eprintln!("[line {:?}] Error {:?}: {:?}", line, location, message);

    unsafe {
        HAD_ERROR = true;
    }
}
