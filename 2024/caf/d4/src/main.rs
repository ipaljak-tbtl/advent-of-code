use std::fs;

use regex::Regex;

fn main() {
    let mut total_xmas_count = 0;
    let data = read_data();

    let mut lines: Vec<&str> = vec![];
    for line in data.lines() {
        total_xmas_count = total_xmas_count + count_xmas(line);
        lines.push(line);
    }

    for i in 3..lines.len() {
        let top = i - 3;
        let top_lines_slice = &lines[top..i + 1];
        total_xmas_count = total_xmas_count + transform_and_sum_xmas(top_lines_slice);
    }

    let mut total_mas_count = 0;
    for i in 0..lines.len() - 2 {
        let mas_lines = &lines[i..i + 3];
        total_mas_count = total_mas_count + mas_count(mas_lines);
    }

    println!("Total XMAS count: {}, Total MAS count: {}", total_xmas_count, total_mas_count);
}

fn mas_count(slice: &[&str]) -> i32 {
    let mut count = 0;
    let lines: Vec<String> = slice.iter().map(|&s| s.to_string()).collect();

    let line0 = lines.get(0).unwrap();
    let line1 = lines.get(1).unwrap();
    let line2 = lines.get(2).unwrap();
    let line_length  = line0.len();

    for i in 0..line_length - 2 {
        let m = line1.chars().nth(i + 1).unwrap();

        let a1 = line0.chars().nth(i).unwrap();
        let a2 = line2.chars().nth(i + 2).unwrap();
        let x1 = format!("{}{}{}", a1,m,a2);

        let b1 = line0.chars().nth(i + 2).unwrap();
        let b2 = line2.chars().nth(i).unwrap();
        let x2 = format!("{}{}{}", b1,m,b2);

        if (x1 == "SAM" || x1 == "MAS") && (x2 == "SAM" || x2 == "MAS") {
            count += 1;
        }
    }
    count
}

fn transform_and_sum_xmas(slice: &[&str]) -> usize {
    let lines_slice: Vec<String> = slice.iter().map(|&s| s.to_string()).collect();
    sum_xmas(vertical_to_horizontal(&lines_slice))
        + sum_xmas(left_shift(&lines_slice))
        + sum_xmas(right_shift(&lines_slice))
}

fn sum_xmas(lines: Vec<String>) -> usize {
    lines.iter().map(|line| count_xmas(line)).sum()
}


fn vertical_to_horizontal(lines: &Vec<String>) -> Vec<String> {
    let line_length = lines.first().unwrap().chars().count();
    transform_lines(lines, 0, line_length,
                    |line0, line1, line2, line3, i|
                        vec![
                            line0.chars().nth(i).unwrap(),
                            line1.chars().nth(i).unwrap(),
                            line2.chars().nth(i).unwrap(),
                            line3.chars().nth(i).unwrap(),
                        ],
    )
}

fn left_shift(lines: &Vec<String>) -> Vec<String> {
    let line_length = lines.first().unwrap().chars().count();
    transform_lines(lines, 0, line_length - 3,
                    |line0, line1, line2, line3, i|
                        vec![
                            line0.chars().nth(i).unwrap(),
                            line1.chars().nth(i + 1).unwrap(),
                            line2.chars().nth(i + 2).unwrap(),
                            line3.chars().nth(i + 3).unwrap(),
                        ],
    )
}

fn right_shift(lines: &Vec<String>) -> Vec<String> {
    let line_length = lines.first().unwrap().chars().count();
    transform_lines(lines, 3, line_length,
                    |line0, line1, line2, line3, i|
                        vec![
                            line0.chars().nth(i).unwrap(),
                            line1.chars().nth(i - 1).unwrap(),
                            line2.chars().nth(i - 2).unwrap(),
                            line3.chars().nth(i - 3).unwrap(),
                        ],
    )
}

fn transform_lines<F>(lines: &Vec<String>, min: usize, max: usize, transform: F) -> Vec<String>
    where
        F: Fn(&String, &String, &String, &String, usize) -> Vec<char> {
    let mut shifted_lines: Vec<String> = vec![];
    for i in min..max {
        let line0 = lines.get(0).unwrap();
        let line1 = lines.get(1).unwrap();
        let line2 = lines.get(2).unwrap();
        let line3 = lines.get(3).unwrap();

        let chars = transform(line0, line1, line2, line3, i);
        shifted_lines.push(chars.into_iter().collect());
    }
    shifted_lines
}

fn count_xmas(line: &str) -> usize {
    count_horizontal(line)
        + count_backwards(line)
}

fn count_horizontal(line: &str) -> usize {
    count_occurrence(line, r"XMAS")
}

fn count_backwards(line: &str) -> usize {
    count_occurrence(line, r"SAMX")
}

fn count_occurrence(line: &str, regex_str: &str) -> usize {
    let regex = Regex::new(regex_str).unwrap();
    regex.find_iter(line).count()
}


fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}
