use std::collections::HashMap;
use std::fs;

fn main() {
    let mut rules: HashMap<String, Vec<String>> = HashMap::new();

    for raw_rule in read_rules().lines() {
        let rule: Vec<String> = split(raw_rule, "|");
        let invalid_page = get_at(&rule, 0);
        let key = get_at(&rule, 1);

        let invalid_pages = rules.entry(key).or_insert(Vec::new());
        invalid_pages.push(invalid_page);
    }

    let mut valid_updates: HashMap<String, Vec<String>> = HashMap::new();
    let mut corrected_updates: HashMap<String, Vec<String>> = HashMap::new();
    for raw_pages in read_updates().lines() {
        let pages: Vec<String> = split(raw_pages, ",");
        if is_valid_update(&rules, &pages) {
            valid_updates.insert(raw_pages.to_string(), pages.clone());
        } else {
            let corrected_update = makeit_valid(&rules, &pages);
            corrected_updates.insert(raw_pages.to_string(), corrected_update.clone());
        }

    }

    let valid_updates_sum: i32 = calculate_sum(valid_updates);
    let corrected_updates_sum: i32 = calculate_sum(corrected_updates);

    print!("Valid updates sum: {}, Corrected updates sum: {}", valid_updates_sum, corrected_updates_sum);
}

fn calculate_sum(updates: HashMap<String, Vec<String>>) -> i32 {
    let mut updates_sum: i32 = 0;
    for valid_update in updates.values() {
        let middle: i32 = valid_update.get((valid_update.len() - 1) / 2).unwrap().parse().unwrap();
        updates_sum = updates_sum + middle;
    }
    updates_sum
}

fn makeit_valid(rules: &HashMap<String, Vec<String>>, pages: &Vec<String>) -> Vec<String> {
    for i in 0..pages.len() {
        let page = pages.get(i).unwrap();
        for j in i + 1..pages.len() {
            let page_rule = rules.get(page);
            let next_page = pages.get(j).unwrap();

            if is_next_page_valid(page_rule, next_page) {
                let mut corrected_pages = pages.clone();
                corrected_pages.swap(i, j);
                return makeit_valid(rules, &corrected_pages);
            }
        }
    }

    pages.clone()
}

fn is_next_page_valid(page_rule: Option<&Vec<String>>, next_page: &String) -> bool {
    !page_rule.is_none() && page_rule.unwrap().contains(next_page)
}

fn is_valid_update(rules: &HashMap<String, Vec<String>>, pages: &Vec<String>) -> bool {
    for i in 0..pages.len() {
        let page = pages.get(i).unwrap();
        for j in i + 1..pages.len() {
            let page_rule = rules.get(page);
            let next_page = pages.get(j).unwrap();

            if is_next_page_valid(page_rule, next_page) {
                return false;
            }
        }
    }
    true
}

fn split(splitting_object: &str, split_by: &str) -> Vec<String> {
    splitting_object.split(split_by).map(|s| s.to_string()).collect()
}

fn get_at(strings: &Vec<String>, i: usize) -> String {
    strings.get(i).unwrap().to_string()
}


fn read_rules() -> String {
    read_data("rules.txt")
}

fn read_updates() -> String {
    read_data("updates.txt")
}

fn read_data(path: &str) -> String {
    fs::read_to_string(path).unwrap()
}
