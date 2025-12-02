use std::fs::read_to_string;
fn main() {
    let mut result: usize = 0;
    for line in read_to_string("input.txt").unwrap().split(',') {
        let mut num = line.split('-');
        let lower: usize = num.next().expect("Should not happen").parse().unwrap();
        let upper: usize = num.next().expect("Should not happen").parse().unwrap();
        for number in lower..=upper {
            let digit_num = number.to_string().len() / 2;
            let first_half = &number.to_string()[..digit_num];
            let second_half = &number.to_string()[digit_num..];
            if first_half == second_half {
                result += number;
            }
        }
    }
    println!("{}", result);
}
