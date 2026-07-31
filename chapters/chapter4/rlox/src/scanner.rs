use crate::token::Token;

struct Scanner {
    source: String,
    tokens: Vec<Token>,
}

impl Scanner {
    fn new(source: String) -> Self {
        Self {
            source,
            tokens: Vec::new(),
        }
    }
}
