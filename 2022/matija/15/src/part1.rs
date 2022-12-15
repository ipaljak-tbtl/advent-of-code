pub fn solve(input: &[String]) -> u32 {
    let mut positions = vec![];

    let ty = 2000000;
    let (mut x_min, mut x_max) = (i32::MAX, i32::MIN);

    for line in input {
        let parts: Vec<&str> = line.split(' ').collect();

        let sx: i32 = parts[2][2..].trim_end_matches(',').parse().unwrap();
        let sy: i32 = parts[3][2..].trim_end_matches(':').parse().unwrap();

        let bx: i32 = parts[8][2..].trim_end_matches(',').parse().unwrap();
        let by: i32 = parts[9][2..].parse().unwrap();

        if (sy - ty).abs() > (sx - bx).abs() + (sy - by).abs() {
            continue;
        }

        positions.push((sx, sy, bx, by));

        let tmp = (sx - bx).abs() + (sy - by).abs() - (sy - ty).abs();

        let tx_min = sx - tmp;
        let tx_max = sx + tmp;

        if tx_min < x_min {
            x_min = tx_min;
        }

        if tx_max > x_max {
            x_max = tx_max;
        }
    }

    let mut result = 0;

    for tx in x_min..(x_max + 1) {
        let mut can_contain = true;

        for (sx, sy, bx, by) in &positions {
            if (&tx, &ty) == (bx, by) {
                can_contain = true;
                break;
            }

            if (sx - tx).abs() + (sy - ty).abs() <= (sx - bx).abs() + (sy - by).abs() {
                can_contain = false;
            }
        }

        if !can_contain {
            result += 1;
        }
    }

    result
}
