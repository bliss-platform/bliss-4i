mod tokenize;
mod readfile;
mod engine;
//Task 1 - read a file from the command line arguments.
use std::env;
use tokenize::tokenize::*;
use readfile::*;

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
