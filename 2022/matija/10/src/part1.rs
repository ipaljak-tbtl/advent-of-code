pub fn solve(input: &[String]) -> i32 {
    let mut x = 1;

    let mut next_cycle = 20;
    let mut cycle = 1;

    let mut sum = 0;

    for line in input {
        let instruction = &line[..4];

        if instruction == "noop" {
            if cycle == next_cycle {
                sum += next_cycle * x;
                next_cycle += 40;
            }

            cycle += 1;
        } else {
            let v: i32 = line[5..].parse().unwrap();

            for _ in 0..2 {
                if cycle == next_cycle {
                    sum += next_cycle * x;
                    next_cycle += 40;
                }

                cycle += 1;
            }

            x += v;
        }
    }

    sum
}
