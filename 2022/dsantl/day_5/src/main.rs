use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn prepare_row(line: &str) -> Vec<char> {
    let mut row = vec![];
    let mut count: usize = 1;
    while count < line.len() {
        row.push(line.chars().nth(count).unwrap());
        count += 4;
    }
    row
}

fn do_command(amount: usize, from: usize, to: usize, columns: &mut Vec<Vec<char>>) {
    let from = from - 1;
    let to = to - 1;
    let mut buffer = vec![];
    for _ in 0..amount {
        let top = columns[from].pop().unwrap();
        buffer.push(top);
    }

    for _ in 0..buffer.len() {
        let top = buffer.pop().unwrap();
        columns[to].push(top);
    }
}

#[allow(dead_code)]
fn print_stacks(columns: &Vec<Vec<char>>) {
    for i in 0..columns.len() {
        for j in 0..columns[i].len() {
            print!("{}", columns[i][j]);
        }
        println!("");
    }
    println!("");
}

fn main() {
    let stdin = io::stdin();

    let mut rows: Vec<Vec<char>> = vec![];

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let row = prepare_row(&line);
        if row[0] == '1' {
            break;
        }
        rows.push(row);
    }

    let mut columns: Vec<Vec<char>> = vec![];

    for _ in 0..rows[0].len() {
        columns.push(vec![]);
    }

    for i in (0..rows.len()).rev() {
        for j in 0..rows[i].len() {
            if rows[i][j] == ' ' {
                continue;
            }
            columns[j].push(rows[i][j]);
        }
    }

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        if split[0] == "move" {
            let amount = split[1].parse::<usize>().unwrap();
            let from = split[3].parse::<usize>().unwrap();
            let to = split[5].parse::<usize>().unwrap();
            do_command(amount, from, to, &mut columns);
        }
    }

    for i in 0..columns.len() {
        let top = columns[i].pop().unwrap();
        print!("{}", top);
    }
    println!();
}
