use std::fs;

pub fn read_file(filename: &str) -> String {
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