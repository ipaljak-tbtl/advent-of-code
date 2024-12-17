use std::{
    collections::HashSet,
    hash::Hash,
    io::{self, BufRead},
    thread,
};

use scan_fmt::scan_fmt;

fn main() {
    let stdin = io::stdin();
    let handle = stdin.lock();

    let lines = handle
        .lines()
        .map(|l| l.unwrap())
        .filter(|l| !l.is_empty())
        .collect::<Vec<_>>();

    let mut A = scan_fmt!(&lines[0], "Register A: {}", usize).unwrap();
    let mut B = scan_fmt!(&lines[1], "Register B: {}", usize).unwrap();
    let mut C = scan_fmt!(&lines[2], "Register C: {}", usize).unwrap();

    let mut IP = 0;

    let mut output = vec![];

    let program = scan_fmt!(&lines[3], "Program: {}", String).unwrap();
    let program = program
        .split(',')
        .map(|x| x.parse::<usize>().unwrap())
        .collect::<Vec<_>>();

    while IP < program.len() {
        let opcode = program[IP];
        let operand = program[IP + 1];

        let get_combo_value = |op| match op {
            x @ 0..=3 => x,
            4 => A,
            5 => B,
            6 => C,
            _ => unreachable!(),
        };

        match opcode {
            0 => {
                A /= 2_usize.pow(get_combo_value(operand) as u32);
            }
            1 => {
                B ^= operand;
            }
            2 => {
                B = get_combo_value(operand) % 8;
            }
            3 => {
                if A != 0 {
                    IP = operand;
                    continue;
                }
            }
            4 => {
                B ^= C;
            }
            5 => {
                output.push(get_combo_value(operand) % 8);
            }
            6 => {
                B = A / 2_usize.pow(get_combo_value(operand) as u32);
            }
            7 => {
                C = A / 2_usize.pow(get_combo_value(operand) as u32);
            }
            _ => unreachable!(),
        }
        IP += 2;
    }

    let output = output
        .into_iter()
        .map(|o| o.to_string())
        .collect::<Vec<_>>()
        .join(",");

    println!("p1: {}", output);

    let mut stack = vec![(0_usize, vec![])];
    let mut visited: HashSet<_> = HashSet::new();

    while let Some((orig_A, orig_output)) = stack.pop() {
        if visited.contains(&(orig_A, orig_output.clone())) {
            continue;
        }

        visited.insert((orig_A, orig_output.clone()));

        let mut B = 0;
        let mut C = 0;
        let mut IP = 0;

        let mut i = 1;
        loop {
            let mut output = vec![];
            let mut A = orig_A + ((i) << { 64 - orig_A.leading_zeros() });
            let start_A = A;
            let mut B = 0;
            let mut C = 0;
            let mut IP = 0;

            while IP < program.len() {
                let opcode = program[IP];
                let operand = program[IP + 1];

                let get_combo_value = |op| match op {
                    x @ 0..=3 => x,
                    4 => A,
                    5 => B,
                    6 => C,
                    _ => unreachable!(),
                };

                match opcode {
                    0 => {
                        A >>= get_combo_value(operand) as u32;
                    }
                    1 => {
                        B ^= operand;
                    }
                    2 => {
                        B = get_combo_value(operand) % 8;
                    }
                    3 => {
                        if A != 0 {
                            IP = operand as usize;
                            continue;
                        }
                    }
                    4 => {
                        B ^= C;
                    }
                    5 => {
                        output.push(get_combo_value(operand) % 8);
                    }
                    6 => {
                        B = A >> get_combo_value(operand) as u32;
                    }
                    7 => {
                        C = A >> get_combo_value(operand) as u32;
                    }
                    _ => unreachable!(),
                }
                IP += 2;
            }

            if program == output {
                println!("p2: {}", start_A);
                return;
            }

            if program.starts_with(&output) && output.len() > orig_output.len() {
                match stack.binary_search_by(|&(a, _)| a.cmp(&start_A).reverse()) {
                    Ok(pos) | Err(pos) => stack.insert(pos, (start_A, output.clone())),
                }
            }

            i += 1;

            if i == 100_000_000 {
                eprintln!("picka");
                break;
            }
        }
    }

    // let n_cpus = num_cpus::get_physical();
    // const RUN_TO: usize = 281_474_976_710_656;

    // let per_cpu = RUN_TO / n_cpus;

    // let (tx, rx) = std::sync::mpsc::channel::<i64>();

    // for tc in 0..n_cpus {
    //     let program = program.clone();
    //     let tx = tx.clone();
    //     let _thread = thread::spawn(move || {
    //         for i in (tc * per_cpu)..((tc + 1) * per_cpu) {
    //             if i % 20_000_000 == 0 {
    //                 println!(
    //                     "tc {}: {}%",
    //                     tc,
    //                     ((i - tc * per_cpu) as f64
    //                         / (((tc + 1) * per_cpu) - (tc * per_cpu)) as f64)
    //                         * 100.0
    //                 );
    //             }
    //             let program = program.clone();
    //             let mut output = vec![];
    //             let mut A = i as i64;
    //             let mut B = 0;
    //             let mut C = 0;
    //             let mut IP = 0;
    //             output.clear();

    //             while IP < program.len() {
    //                 let opcode = program[IP];
    //                 let operand = program[IP + 1];

    //                 let get_combo_value = |op| match op {
    //                     x @ 0..=3 => x,
    //                     4 => A,
    //                     5 => B,
    //                     6 => C,
    //                     _ => unreachable!(),
    //                 };

    //                 match opcode {
    //                     0 => {
    //                         A >>= get_combo_value(operand) as u32;
    //                     }
    //                     1 => {
    //                         B ^= operand;
    //                     }
    //                     2 => {
    //                         B = get_combo_value(operand) % 8;
    //                     }
    //                     3 => {
    //                         if A != 0 {
    //                             IP = operand as usize;
    //                             continue;
    //                         }
    //                     }
    //                     4 => {
    //                         B ^= C;
    //                     }
    //                     5 => {
    //                         output.push(get_combo_value(operand) % 8);
    //                     }
    //                     6 => {
    //                         B = A >> get_combo_value(operand) as u32;
    //                     }
    //                     7 => {
    //                         C = A >> get_combo_value(operand) as u32;
    //                     }
    //                     _ => unreachable!(),
    //                 }
    //                 IP += 2;

    //                 if !program.starts_with(&output) {
    //                     break;
    //                 }
    //             }

    //             if program == output {
    //                 tx.send(i as i64).unwrap();
    //                 break;
    //             }
    //         }
    //     });
    // }

    // let p2 = rx.recv().unwrap();
    // println!("p2: {}", p2);
}
