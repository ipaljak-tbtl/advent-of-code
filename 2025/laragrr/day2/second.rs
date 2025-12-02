use std::fs::read_to_string;
fn main() {
    let mut result: usize = 0;
    for line in read_to_string("input.txt").unwrap().split(',') {
        let mut num = line.split('-');
        let lower: usize = num.next().expect("Should not happen").parse().unwrap();
        let upper: usize = num.next().expect("Should not happen").parse().unwrap();
        'a: for number in lower..=upper {
            let digit_num = number.to_string().len();
            for size in 1..15 {
                if digit_num <= size {
                    break;
                }
                if number.to_string()[..size].repeat(digit_num / size) == number.to_string() {
                    result += number;
                    continue 'a;
                }
            }
        }
    }
    println!("{}", result);
}
