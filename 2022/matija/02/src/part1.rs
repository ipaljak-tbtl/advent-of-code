pub fn solve(input: &[String]) -> u32 {
    let mut score = 0;

    for line in input {
        let chars: Vec<char> = line.chars().collect();
        let p1 = chars[0];
        let p2 = chars[2];

        if p2 == 'X' {
            score += 1;
            if p1 == 'A' {
                score += 3;
            } else if p1 == 'C' {
                score += 6;
            }
        } else if p2 == 'Y' {
            score += 2;
            if p1 == 'B' {
                score += 3;
            } else if p1 == 'A' {
                score += 6;
            }
        } else if p2 == 'Z' {
            score += 3;
            if p1 == 'C' {
                score += 3;
            } else if p1 == 'B' {
                score += 6;
            }
        }
    }

    score
}
