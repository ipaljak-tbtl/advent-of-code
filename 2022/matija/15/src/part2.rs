pub fn solve(input: &[String]) -> u128 {
    const N_MAX: i32 = 4000000;

    let mut positions = vec![];

    let (mut x_min, mut x_max) = (i32::MAX, i32::MIN);
    let (mut y_min, mut y_max) = (i32::MAX, i32::MIN);

    for line in input {
        let parts: Vec<&str> = line.split(' ').collect();

        let sx: i32 = parts[2][2..].trim_end_matches(',').parse().unwrap();
        let sy: i32 = parts[3][2..].trim_end_matches(':').parse().unwrap();

        let bx: i32 = parts[8][2..].trim_end_matches(',').parse().unwrap();
        let by: i32 = parts[9][2..].parse().unwrap();

        positions.push((sx, sy, bx, by));

        x_min = x_min.min(sx.max(0));
        x_max = x_max.max(sx.min(N_MAX));
        y_min = y_min.min(sy.max(0));
        y_max = y_max.max(sy.min(N_MAX));
    }

    for ty in y_min..(y_max + 1) {
        let mut intervals = vec![];

        for (sx, sy, bx, by) in &positions {
            if (sy - ty).abs() > (sx - bx).abs() + (sy - by).abs() {
                continue;
            }

            let tmp = (sx - bx).abs() + (sy - by).abs() - (sy - ty).abs();

            let tx_min = (sx - tmp).max(0);
            let tx_max = (sx + tmp).min(N_MAX);

            if tx_min > N_MAX || tx_max < 0 {
                continue;
            }

            intervals.push((tx_min, tx_max));
        }

        intervals.sort_by(|i1, i2| i1.0.cmp(&i2.0));

        let mut merged_intervals = vec![];
        merged_intervals.push(intervals[0]);

        for i in 1..intervals.len() {
            let prev = merged_intervals.pop().unwrap();

            if intervals[i].0 > prev.1 {
                merged_intervals.push(prev);
                merged_intervals.push(intervals[i]);
            } else if intervals[i].1 > prev.1 {
                merged_intervals.push((prev.0, intervals[i].1));
            } else {
                merged_intervals.push(prev);
            }
        }

        if merged_intervals.len() > 1 {
            return (merged_intervals[0].1 + 1) as u128 * N_MAX as u128 + ty as u128;
        }
    }

    0
}
