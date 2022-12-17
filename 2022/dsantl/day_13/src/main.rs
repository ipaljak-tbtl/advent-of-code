use std::cmp::max;
use std::cmp::Ordering;
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

fn cmp_ord(left: &Element, right: &Element) -> Ordering {
    let result = cmp(left, right);

    if result == 0 {
        return Ordering::Equal;
    }

    if result > 0 {
        return Ordering::Less;
    }

    Ordering::Greater
}

fn main() {
    let stdin = io::stdin();

    let mut list = vec![];

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        if line == "" {
            continue;
        }
        list.push(parse_list(line));
    }

    list.push(parse_list("[[2]]".to_owned()));
    list.push(parse_list("[[6]]".to_owned()));

    let two = parse_list("[[2]]".to_owned());
    let six = parse_list("[[6]]".to_owned());

    list.sort_by(|a, b| cmp_ord(&a, &b));

    let mut result = 1;
    for (index, list) in list.iter().enumerate() {
        if cmp(&list, &two) == 0 {
            result *= index + 1;
        }
        if cmp(&list, &six) == 0 {
            result *= index + 1;
        }
    }
    println!("{}", result);
}
