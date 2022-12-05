pub fn solve(input: &[String]) -> u32 {
    let mut score = 0;

    for line in input {
        let chars: Vec<char> = line.chars().collect();
        let p1 = chars[0];
        let p2 = chars[2];

        if p2 == 'X' {
            if p1 == 'A' {
                score += 3;
            } else if p1 == 'B' {
                score += 1;
            } else {
                score += 2;
            }
        } else if p2 == 'Y' {
            score += 3;
            if p1 == 'A' {
                score += 1;
            } else if p1 == 'B' {
                score += 2;
            } else {
                score += 3;
            }
        } else if p2 == 'Z' {
            score += 6;
            if p1 == 'A' {
                score += 2;
            } else if p1 == 'B' {
                score += 3;
            } else {
                score += 1;
            }
        }
    }

    score
}
