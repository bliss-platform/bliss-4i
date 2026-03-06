pub mod tokenize {

    use log::Logger;
    use regex::Regex;
    use std::{collections::HashSet, process::exit};

    #[derive(Debug, Clone, Copy)]
    pub enum CoarseTokens {
        Literal,
        String,
        Number,
        Symbol,
    }

    pub struct Token {
        token_type: CoarseTokens,
        value: String,
    }

    impl std::fmt::Display for Token {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            // You can format this however you want your token to look when printed!
            // Example: "[TokenType: value]"
            write!(f, "[ {:?}: {} ]", self.token_type, self.value)
        }
    }

    fn compare_shapes(source: String, ch: char) -> Option<CoarseTokens> {
        let literal_shape = Regex::new(r"^[a-zA-Z_][a-zA-Z0-9_]*$").unwrap();
        let numeric_shape = Regex::new(r"^[0-9]*$").unwrap();

        let mut comparator: String = source.clone();
        comparator.push(ch);

        if literal_shape.is_match(&source) && literal_shape.is_match(&comparator) {
            return Option::Some(CoarseTokens::Literal);
        }

        if numeric_shape.is_match(&source) && numeric_shape.is_match(&comparator) {
            return Option::Some(CoarseTokens::Number);
        }

        Option::None
    }

    enum LexingMode {
        Default,
        Consume,
    }

    fn format_program(program: &str, line: usize, col: usize) -> String {
        //get the line itself
        let mut pad = String::from("");
        let idx = format!("{}", line);
        let mut basic_pad = String::from("");
        
        let mut i = 1;
        while i <= col {
       		pad.push(' ');
         	i+=1;
        }
        
        i = 0;
        while i < idx.len() {
       		basic_pad.push(' ');
         	i+=1;
        }
        
        pad.push('^');
        
        let __temp = String::from(program);
        let line_str = __temp.split('\n').nth(line - 1);
        let formatted = format!(
            "{} |\n{} | {}\n{} | {}",
            basic_pad,
            line,
            match line_str {
                Some(v) => v,
                None => {
                    Logger::new("INTERPRETER", "4IR").error(999, "Internal System Error", "This error is due to malfunction in the software itself.\nPlease create an issue here: https://github.com/bliss-platform/bliss-4i");
                    exit(1);
                }
            },
            basic_pad,
            pad
        );
        
        String::from(formatted)
    }

    pub fn tokenize_program(program: &str) -> Vec<Token> {
        //use the shape method instead.
        //let's define the shape
        //but what happens if the shape changes? -> so far the shape does not change so we are safe.

        let mut line: usize = 1;
        let mut col: usize = 1;
        let mut tokens: Vec<Token> = vec![];
        let mut buffer: String = String::from("");
        let mut mode: LexingMode = LexingMode::Default;
        let mut escape: bool = false;
        let mut present_token_type: Option<CoarseTokens> = Option::None;
        let mut symbol_rules: HashSet<char> = HashSet::new();

        for ch in "`~!@#$%^&*()_+=-{}[]|\\:;'?/>.<,".chars() {
            symbol_rules.insert(ch);
        }

        //I have to manually control the progression.

        for ch in program.chars() {
            match mode {
                LexingMode::Consume => {
                    if ch == '\n' {
                        //newlines are not allowed.
                        Logger::new("INTERPRETER", "4IR").error(
                            001,
                            "Invalid Newline",
                            &format!("Strings cannot contain newlines\n{}", format_program(program, line, col)),
                        );
                        exit(1);
                    }

                    if ch == '\\' {
                        escape = true;
                        buffer.push('\\');
                        //blind consumption
                        continue;
                    }

                    if escape == true {
                        buffer.push(ch);
                        escape = false;
                    } else if ch == '"' {
                        mode = LexingMode::Default;

                        tokens.push(Token {
                            value: buffer.clone(),
                            token_type: CoarseTokens::String,
                        });

                        buffer.clear();
                        continue;
                    } else {
                        buffer.push(ch);
                    }
                }

                LexingMode::Default => {
                    if (ch.is_whitespace() || ch == '\n' || ch == '\t') && buffer.len() == 0 {
                        continue;
                    }

                    if buffer.len() == 0 {
                        if ch == '"' {
                            mode = LexingMode::Consume;
                            continue;
                        }

                        buffer.push(ch);
                        present_token_type = compare_shapes(buffer.clone(), ch);
                    } else {
                        match compare_shapes(buffer.clone(), ch) {
                            Some(token) => {
                                present_token_type = Option::Some(token);
                                buffer.push(ch);
                            }
                            None => {
                                if symbol_rules.contains(&ch) {
                                    //cutoff the previous token
                                    tokens.push(Token {
                                        value: buffer.clone(),
                                        token_type: match present_token_type.clone() {
                                            Some(token_type) => token_type,
                                            None => CoarseTokens::Symbol,
                                        },
                                    });

                                    tokens.push(Token {
                                        value: String::from(ch),
                                        token_type: CoarseTokens::Symbol,
                                    });

                                    buffer.clear();
                                } else if ch == '"' {
                                    mode = LexingMode::Consume;
                                    //consume the string.
                                } else {
                                    //we can have newlines, spaces, strings and whatnot.
                                    //since shape is different
                                    tokens.push(Token {
                                        value: buffer.clone(),
                                        token_type: match present_token_type.clone() {
                                            Some(token_type) => token_type,
                                            None => CoarseTokens::Symbol,
                                        },
                                    });

                                    present_token_type = Option::None;
                                    buffer.clear();
                                    if !(ch.is_whitespace() || ch == '\n' || ch == '\t') {
                                        if ch == '"' {
                                            mode = LexingMode::Consume;
                                            continue;
                                        }
                                        buffer.push(ch); //unanalyzed character
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if ch == '\n' {
                line += 1;
                col = 1;
            } else {
                col += 1;
            }
        }

        tokens
    }
}
