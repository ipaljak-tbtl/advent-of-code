use std::fs;

fn main() {
    let mut safe_count = 0;
    let mut tolerant_safe_count = 0;
    let raw = read_data();

    for line in raw.lines() {
        let report = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        if is_report_safe(&report) {
            safe_count = safe_count + 1;
        } else if is_report_tolerant_safe(&report) {
            tolerant_safe_count = tolerant_safe_count + 1;
        }
    }
    println!("Safe count: {}, Tolerant safe {}, Total safe: {}", safe_count, tolerant_safe_count, safe_count + tolerant_safe_count);
}

fn is_report_safe(report: &Vec<i32>) -> bool {
    if report.iter().count() == 1 {
        return true;
    }

    let item1  = *report.get(0).unwrap();
    let item2  = *report.get(1).unwrap();
    return if item1 == item2 {
        false
    } else if item1 > item2 {
        is_desc_safe(report)
    } else {
        is_asc_safe(report)
    }
}

fn is_report_tolerant_safe(report: &Vec<i32>) -> bool {
    for i in 0..report.len() {
        let mut modified_report = report.clone();
        modified_report.remove(i);
        if is_report_safe(&modified_report) {
            return true;
        }
    }

    return false
}

fn is_desc_safe(report: &Vec<i32>) -> bool {
    return is_safe(report, |level, next_level| level > next_level);
}

fn is_asc_safe(report: &Vec<i32>) -> bool {
    return is_safe(report, |level, next_level| level < next_level);
}

fn is_safe<F>(report: &Vec<i32>, safe_condition: F) -> bool
where
F : Fn(i32, i32) -> bool {
    for (i, level) in report.iter().enumerate() {
        if i == report.iter().count() - 1 {
            return true
        }

        let next_level = report.get(i + 1).unwrap();
        if !(safe_condition(*level, *next_level) && is_in_safe_range(*level, *next_level)) {
            return false;
        }

    }

    return true;
}

fn is_in_safe_range(a: i32, b: i32) -> bool {
    let c = (a - b).abs();
    c > 0 && c < 4
}

fn read_data() -> String {
    fs::read_to_string("data.txt").unwrap()
}
