use std::fs;
fn main() {
    println!("Opening and encrypting ./flag...");
    let sbox = [17, 13, 20, 14, 3, 23, 28, 30, 21, 4, 18, 12, 0, 25, 10, 27, 22, 16, 8, 6, 19, 7, 11, 24, 29, 31, 9, 5, 26, 1, 2, 15];
    let mut result: Vec<char> = Vec::new();
    let contents: Vec<char> = fs::read_to_string("./flag").expect("Error reading ./flag").chars().collect();
    if contents.len() != 32 {
        println!("Flag file not 32, exiting...");
        return;
    }
    for c in 0..32 {
        result.push(contents[sbox[c]]);
    }
    let out_string =  result.iter().cloned().collect::<String>();
    fs::write("./flag_out", out_string.as_bytes()).unwrap();
    println!("Done");
}
