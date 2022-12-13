pub fn solve(input: &[String]) -> String {
    let mut x = 1;

    let mut out = String::new();
    let mut draw_position: i32 = 0;

    let mut next_cycle = 40;
    let mut cycle = 1;

    for line in input {
        let instruction = &line[..4];

        if instruction == "noop" {
            if draw_position.abs_diff(x) <= 1 {
                out.push('#');
            } else {
                out.push('.');
            }

            draw_position += 1;

            if cycle == next_cycle {
                next_cycle += 40;
                out.push('\n');
                draw_position = 0;
            }

            cycle += 1;
        } else {
            let v: i32 = line[5..].parse().unwrap();

            for _ in 0..2 {
                if draw_position.abs_diff(x) <= 1 {
                    out.push('#');
                } else {
                    out.push('.');
                }

                draw_position += 1;

                if cycle == next_cycle {
                    next_cycle += 40;
                    out.push('\n');
                    draw_position = 0;
                }

                cycle += 1;
            }

            x += v;
        }
    }

    String::from(out.trim_end())
}
