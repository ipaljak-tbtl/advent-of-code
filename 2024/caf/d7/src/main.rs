use std::fs;

fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}

fn main() {
    let mut sum: usize = 0;
    let mut concat_sum: usize = 0;
    for line in read_data().lines() {
        let equation: Vec<String> = line.split(":").map(|x| x.to_string()).collect();
        let result: usize = equation[0].trim().parse().unwrap();
        let numbers = equation[1].trim().split(" ").map(|x| x.parse().unwrap()).collect::<Vec<usize>>();
        if can_be_made_true(result, &numbers) {
            sum += result;
        } else if can_be_made_true_with_concat(result, &numbers) {
            concat_sum += result;
        }
    }

    println!("Sum: {}, Concat sum: {} Total sum: {}", sum, concat_sum, sum + concat_sum);
}

fn can_be_made_true(result: usize, numbers: &Vec<usize>) -> bool {
    let operator_count = numbers.len() - 1;

    for combo in 0..2usize.pow(operator_count as u32) {
        if result == calculate_combo_sum(combo, numbers) {
            return true;
        }
    }
    false
}


fn calculate_combo_sum(combo: usize, numbers: &[usize]) -> usize {
    let operator_count = numbers.len() - 1;
    let mut combo_sum = numbers[0];
    for i in (0..operator_count).rev() {
        let number = numbers[operator_count - i];
        if (combo >> i) & 1 == 1 {
            combo_sum = combo_sum * number;
        } else {
            combo_sum = combo_sum + number;
        }
    }

    combo_sum
}

fn can_be_made_true_with_concat(result: usize, numbers: &Vec<usize>) -> bool {
    let operator_count = numbers.len() - 1;

    println!("Numbers: {:?}", numbers);
    for combo in 0..3usize.pow(operator_count as u32) {
        if result == calculate_combo_sum_with_concat(combo, numbers) {
            println!("GOOD COMBO: {}", combo);
            return true;
        }
    }

    false
}

fn calculate_combo_sum_with_concat(combo: usize, numbers: &[usize]) -> usize {
    let operator_count = numbers.len() - 1;
    let mut combo_sum = numbers[0];
    for i in (0..operator_count).rev() {
        let number = numbers[operator_count - i];
        let operator_type = (combo / 3usize.pow(i as u32)) % 3;
        if operator_type == 0 {
            combo_sum = combo_sum + number;
        } else if operator_type == 1 {
            combo_sum = combo_sum * number;
        } else {
            combo_sum = (combo_sum.to_string() + &number.to_string()).parse().unwrap();
        }
    }

    combo_sum
}


