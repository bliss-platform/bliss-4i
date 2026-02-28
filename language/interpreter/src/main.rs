//Task 1 - read a file from the command line arguments.
use std::fs;
use std::env;
use std::collections::HashSet;

#[derive(Debug)]
enum CoarseTokens {
	Default,
	Literal,
	String,
	Number,
	Symbol
}

struct Token {
	token_type: CoarseTokens,
	value: String
}

impl std::fmt::Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        // You can format this however you want your token to look when printed!
        // Example: "[TokenType: value]"
        write!(f, "[ {:?}: \"{}\" ]", self.token_type, self.value)
    }
}

fn consume_string(source: &str, index: &mut usize) -> String {
	
	let mut destination: String = String::from("");
	let mut blind_consume: bool = false;
	let mut terminated: bool = false;
	
	for ch in source.chars() {
		
		if blind_consume {
			
			destination.push(ch);
			blind_consume = false;
			
		} else if ch == '\\' {
			
			//consume the character
			blind_consume = true;
			
		} else if ch == '"' {
			
			terminated = true;
			break;
			
		} else {
			
			destination.push(ch);
		
		}
		
		*index += 1;
		
	}
	
	if !terminated {
		//non termination error.
		panic!("String literal does not terminate")
	}
	
	return destination;
	
}

fn tokenize_program(program: &str) -> Vec<Token> {

	let mut line: u32 = 1;
	let mut col: u32 = 1;
	let mut char_index: usize = 0;
	
	let mut buffer: String = String::from("");
	let mut buffer_type: CoarseTokens = CoarseTokens::Default;
	
	let mut literal_rules: HashSet<char> = HashSet::new();
	for ch in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_".chars() {
		literal_rules.insert(ch);
	}
	
	let mut numeric_rules: HashSet<char> = HashSet::new();
	for ch in "0123456789".chars() {
		numeric_rules.insert(ch);
	}
	
	let mut symbol_rules: HashSet<char> = HashSet::new();
	for ch in "+-*/-={}[]()~`!@#$%^&*:;',.<>?/|\\".chars() {
		symbol_rules.insert(ch);
	}
	
	let mut tokens: Vec<Token> = vec![];
	
	//rules for tokenization
	
	while char_index != program.len() {
		
		let character = match program.chars().nth(char_index) {
			Some(c) => c,
			None => panic!("Internal error")
		};
		
		if buffer.len() == 0 {
			//then simple extraction and rulebook play
			buffer.push(character);
			
			if character == '\n' {
				line += 1;
				col = 1;
				char_index+=1;
				continue;
			}
			//I can safetly ignore these.
			if character == ' ' || character == '\t' {
				char_index+=1;
				continue;
			}
			
			if literal_rules.contains(&character) {
				buffer_type = CoarseTokens::Literal;
			} else if numeric_rules.contains(&character) {
				buffer_type = CoarseTokens::Number;
			} else if symbol_rules.contains(&character) {
				buffer_type = CoarseTokens::Symbol;
			} else if character == '"' {
				buffer_type = CoarseTokens::String
			} else {
				panic!(
					"Invalid character \"{character}\" encountered at line: {line} column: {col}"
				);
			}
			
			char_index+=1;
			continue;
			
		}
		
		match buffer_type {
			CoarseTokens::Default => {
				//ignore
			}
			CoarseTokens::Literal => {
				if literal_rules.contains(&character) || numeric_rules.contains(&character) {
					buffer.push(character);
				} else {
					tokens.push( 
						Token { 
							token_type: CoarseTokens::Literal, 
							value: buffer.clone()
						}
					);
					
					buffer.clear();
				}
			}
			
			CoarseTokens::String => {
				//consume till we encounter something.
				tokens.push(
					Token {
						token_type: CoarseTokens::String,
						//hacks for now, optimize later
						value: consume_string(&program[char_index..], &mut char_index)
					}
				);
				
				buffer.clear();
			}
			
			CoarseTokens::Number => {
				if numeric_rules.contains(&character) {
					buffer.push(character);
				} else {
					tokens.push( 
						Token { 
							token_type: CoarseTokens::Number, 
							value: buffer.clone()
						}
					);
					
					buffer.clear();
				}
			}
			CoarseTokens::Symbol => {
				//each symbol is a token itself.
				tokens.push(
					Token {
						token_type: CoarseTokens::Symbol,
						value: buffer.clone()
					}
				);
				
				buffer.clear();
			}
		}
				
		col += 1;
		char_index+=1;
		
	}
	
	tokens
	
}

fn read_file(filename: &str) -> String {
	
	let file = fs::read_to_string(filename);
	let file_data: String;
	
	match file {
		Ok(data) => {
			//rust has late assignments!
			file_data = data;
		}
		
		Err(_) => {
			panic!("Error: Invalid Source File");
		}
    }
	
    return file_data;
	
}

fn main() {
	
	//see the standard IO.
	let args: Vec<String> = env::args().collect();
	
	if args.len() != 2 {
		println!("Welcome to Bliss Interpreter!");
		println!("Run the following command: blissinterp <filename>.bls");
	} else {
		
		//actual program starts here
		let program: String = 
			read_file(
				args.get(1)
					.expect("This is an internal error - please report it to github issues: https://github.com/bliss-platform/bliss-4i/issues")
			);
		
		let tokens = tokenize_program(&program);
		
		for token in tokens {
			println!("Token: {token}")
		}
		//tokenize the program
		
	}
	
}