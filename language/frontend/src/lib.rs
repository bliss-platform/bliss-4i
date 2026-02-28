pub enum StructureToken {
    LeftParen, RightParen // ( )
    LeftBrace, RightBrace // { }
    LeftBracket, RightBracket // [ ]
    Comma, SemiColon // , ;
}

pub enum KeywordToken {
    Fx,
    Data, Action, Bind,
    If, Elif, Else,
    For,
    Return,
}

pub enum MathToken {
    Plus,
    Minus,
    Multiply,
    Divide,
    GreaterThan,
    LessThan,
    Equal,
}

pub enum TokenKind {
    Number(f64),
    Identifier(String),
    Math(MathToken),
    Keyword(KeywordToken),
    Structure(StructureToken),
}

pub struct Token {
    kind: TokenKind,
    line: usize,
    column: usize,
}

enum LexicalState {
    Default,
    StringLiteral,
    Comment,
}

pub fn tokenize( input: &str ) -> Vector<Token> {
    // Tokenization logic goes here
    let mut tokens = Vector<Token>::new();
    let mut buffer = Vector<char>::new();
    let mut state = LexicalState::Default;

    for (line_num, line) in input.lines().enumerate() {
        for (col_num, ch) in line.chars().enumerate() {

            buffer.push(ch); //first add the character to the buffer, then decide what to do with it based on the state

            match state {
                LexicalState::Default => {
                    
                    

                },
                LexicalState::StringLiteral => {
                    // Handle string literal state
                },
                LexicalState::Comment => {
                    // Handle comment state
                },
            }
        }
    }

}