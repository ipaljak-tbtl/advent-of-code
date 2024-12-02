use std::fs;

fn main() {
    println!("Hello, world!");
}

fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}

fn parse_to_sorted_lists(raw: &String) -> (Vec<i32>, Vec<i32>) {
    let mut list1: Vec<i32> = vec![];
    let mut list2: Vec<i32> = vec![];

    for line in raw.lines() {
        let vec: Vec<&str> = line.split_whitespace().collect();
        list1.push(vec.get(0).unwrap().parse().unwrap());
        list2.push(vec.get(1).unwrap().parse().unwrap());
    }

    list1.sort();
    list2.sort();
    (list1, list2)
}

fn calculate_total_distance_and_similarity_score(list1: Vec<i32>, list2: Vec<i32>) -> (i32, i32) {
    let mut distance_list: Vec<i32> = vec![];
    let mut similarity_list: Vec<i32> = vec![];
    for (i, item) in list1.iter().enumerate() {
        similarity_list.push(*item * count_occurrences(item, &list2));
        let distance = item - list2.get(i).unwrap();
        distance_list.push(distance.abs());

    }

    (distance_list.iter().sum(), similarity_list.iter().sum())
}

fn count_occurrences(item: &i32, list: &Vec<i32>) -> i32 {
    list.iter().filter(|&&x| x == *item).count() as i32
}


#[cfg(test)]
mod tests {
    use crate::{calculate_total_distance_and_similarity_score, parse_to_sorted_lists, read_data};

    #[test]
    fn data_read_is_not_empty() {
        assert_eq!(read_data().is_empty(), false);
    }

    #[test]
    fn total_distance_is_3714264_and_similarity_score_is_1() {
        let (list1, list2) = parse_to_sorted_lists(&read_data());
        let (total_distance, similarity_score) = calculate_total_distance_and_similarity_score(list1, list2);
        assert_eq!(total_distance, 3714264);
        assert_eq!(similarity_score, 18805872);
    }
}
