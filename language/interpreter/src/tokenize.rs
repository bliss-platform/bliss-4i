pub mod tokenize {

    use regex::Regex;
    use std::collections::HashSet;

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

    pub fn tokenize_program(program: &str) -> Vec<Token> {
        //use the shape method instead.
        //let's define the shape
        //but what happens if the shape changes? -> so far the shape does not change so we are safe.
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
        }

        tokens
    }
}
