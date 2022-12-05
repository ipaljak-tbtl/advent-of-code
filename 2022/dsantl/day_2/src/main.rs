use std::io::{self, BufRead};

fn split_line(line: &str) -> Vec<&str> {
    let split = line.split(" ");
    split.collect::<Vec<&str>>()
}

fn win(player: &str) -> &str {
    match player {
        "A" => "Y",
        "B" => "Z",
        "C" => "X",
        _ => unimplemented!(),
    }
}

fn lose(player: &str) -> &str {
    match player {
        "A" => "Z",
        "B" => "X",
        "C" => "Y",
        _ => unimplemented!(),
    }
}

fn draw(player: &str) -> &str {
    match player {
        "A" => "X",
        "B" => "Y",
        "C" => "Z",
        _ => unimplemented!(),
    }
}

fn main() {
    let stdin = io::stdin();

    let mut total = 0;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line);

        let choice = match split[1] {
            "X" => lose(split[0]),
            "Y" => draw(split[0]),
            "Z" => win(split[0]),
            _ => unimplemented!(),
        };

        total += match choice {
            "X" => 1,
            "Y" => 2,
            "Z" => 3,
            _ => 0,
        };

        total += match (split[0], choice) {
            ("A", "X") => 3,
            ("A", "Y") => 6,
            ("B", "Y") => 3,
            ("B", "Z") => 6,
            ("C", "X") => 6,
            ("C", "Z") => 3,
            _ => 0,
        };
    }
    println!("{}", total);
}
