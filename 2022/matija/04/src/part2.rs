use regex::Regex;

pub fn solve(input: &[String]) -> u32 {
    let re = Regex::new(r"^(\d+)-(\d+),(\d+)-(\d+)$").unwrap();

    let mut cnt = 0;
    for line in input {
        let cap = re.captures(line).unwrap();

        let l1: u32 = cap.get(1).unwrap().as_str().parse().unwrap();
        let r1: u32 = cap.get(2).unwrap().as_str().parse().unwrap();
        let l2: u32 = cap.get(3).unwrap().as_str().parse().unwrap();
        let r2: u32 = cap.get(4).unwrap().as_str().parse().unwrap();

        if l1 >= l2 && l1 <= r2 || r1 >= l2 && r1 <= r2 || l1 < l2 && r1 > r2 {
            cnt += 1;
        }
    }

    cnt
}
