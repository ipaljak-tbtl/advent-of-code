use std::cmp::max;
use std::io::{self, BufRead};

enum Element {
    List(Vec<Element>),
    Number(i32),
}

fn parse_list(list: String) -> Element {
    let mut stack = vec![];
    let mut tmp = "".to_owned();

    for c in list.chars() {
        match c {
            '[' => stack.push(vec![]),
            ']' => {
                let mut complete_list = stack.pop().unwrap();
                if tmp != "" {
                    complete_list.push(Element::Number(tmp.parse::<i32>().unwrap()));
                    tmp = "".to_owned();
                }
                if stack.is_empty() {
                    return Element::List(complete_list);
                }
                let last = stack.len() - 1;
                stack[last].push(Element::List(complete_list));
            }
            ',' => {
                if tmp != "" {
                    let last = stack.len() - 1;
                    stack[last].push(Element::Number(tmp.parse::<i32>().unwrap()));
                    tmp = "".to_owned();
                }
            }
            c => tmp.push(c),
        };
    }

    unreachable!();
}

fn cmp(left: &Element, right: &Element) -> i32 {
    match (left, right) {
        (Element::Number(a), Element::Number(b)) => b - a,
        (Element::List(a), Element::List(b)) => {
            let max_len = max(a.len(), b.len());
            for i in 0..max_len {
                if a.len() == i {
                    return 1;
                }
                if b.len() == i {
                    return -1;
                }
                let result = cmp(&a[i], &b[i]);
                if result == 0 {
                    continue;
                }
                return result;
            }
            0
        }
        (Element::Number(a), b) => cmp(&Element::List(vec![Element::Number(*a)]), &b),
        (a, Element::Number(b)) => cmp(&a, &Element::List(vec![Element::Number(*b)])),
    }
}

fn main() {
    let stdin = io::stdin();

    let mut left = Element::List(vec![]);
    let mut right = Element::List(vec![]);

    let mut sum = 0;
    let mut counter = 1;
    for (index, line) in stdin.lock().lines().enumerate() {
        let line = line.unwrap();
        match index % 3 {
            0 => left = parse_list(line),
            1 => right = parse_list(line),
            2 => {
                let r = cmp(&left, &right);
                if r > 0 {
                    sum += counter;
                }
                counter += 1;
            }
            _ => unreachable!(),
        }
    }

    let r = cmp(&left, &right);
    if r > 0 {
        sum += counter;
    }

    println!("{}", sum);
}
