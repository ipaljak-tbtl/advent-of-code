use std::fs;
use regex::Regex;

fn main() {
    let data = read_data();
    let multiplications = extract_multiplications(&data);
    let enabled_multiplications = extract_enabled_multiplications(data);

    println!("Task1...");
    multiply_and_sum(multiplications);
    println!("Task2...");
    multiply_and_sum(enabled_multiplications);
}

fn multiply_and_sum(multiplications: Vec<String>) {
    let mut result: i32 = 0;
    for mult in multiplications {
        let mut split = mult.split(",");
        let first = split.next().unwrap();
        let second = split.next().unwrap();
        let x: i32 = first.replace("mul(", "").parse().unwrap();
        let y: i32 = second.replace(")", "").parse().unwrap();
        result = result + x * y;
    }
    println!("multiplications: {} ", result);
}

fn extract_multiplications(data: &String) -> Vec<String> {
    let regular_expression = Regex::new(r"mul\(\d{1,3},\d{1,3}\)").unwrap();
    regular_expression.find_iter(&data)
        .map(|c| c.as_str().to_string())
        .collect()
}

fn extract_enabled_multiplications(mut data: String) -> Vec<String> {
    data = data.replace("\n", "");
    let regular_expression = Regex::new(r"don't\(\)(.*?)do\(\)").unwrap();
    let donts: Vec<String> = regular_expression.find_iter(&data)
        .map(|c| c.as_str().to_string())
        .collect();
    for dont in donts {
        data = data.replace(&dont, "");
    }
    extract_multiplications(&data)
}


fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}

#[cfg(test)]
mod tests {
    use crate::{extract_enabled_multiplications, extract_multiplications};

    #[test]
    fn extracting_multiplications() {
        assert_eq!(extract_multiplications(&"mul(1,1)".to_string()).len(), 1);
        assert_eq!(extract_multiplications(&"'{}mul(339,896)>^+!)^mul(799,303)don't()>mul(188,763)'<};who()select()%;+mul(924,355)mul(492,757) what()mul(582,171)]".to_string()).len(), 6);
    }

    #[test]
    fn extracting_enabled_multiplications() {
        assert_eq!(extract_enabled_multiplications("'{}mul(339,896)>^+!)^mul(799,303)don't()>mul(188,763)'<};who()select()%;+mul(924,355)do()mul(492,757) what()mul(582,171)]".to_string()).len(), 4);
    }
}
