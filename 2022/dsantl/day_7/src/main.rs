use std::collections::HashMap;
use std::io::{self, BufRead};

fn split_line<'a>(line: &'a str, delimiter: &'a str) -> Vec<&'a str> {
    let split = line.split(delimiter);
    split.collect::<Vec<&str>>()
}

fn parent_dir(dir: &str) -> String {
    let split = split_line(dir, "/");
    let except_last = &split[0..split.len() - 2];
    let mut path = "/".to_owned();
    for elem in except_last {
        if *elem == "" {
            continue;
        }
        path = format!("{}{}/", path, elem);
    }
    path
}

fn parents(dir: &str) -> Vec<String> {
    let mut paths = vec![];
    let split = split_line(dir, "/");
    let mut path = "".to_owned();

    for elem in &split[0..split.len() - 1] {
        if *elem == "" {
            paths.push("/".to_owned());
            continue;
        }
        path = format!("{}/{}", path, elem);
        paths.push(path.clone());
    }

    paths
}
fn main() {
    let stdin = io::stdin();

    let mut file_system: HashMap<String, u32> = HashMap::new();
    let mut dir_system: HashMap<String, u32> = HashMap::new();
    let mut current_dir: String = "/".to_owned();
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let split = split_line(&line, " ");
        match split[0] {
            "$" => match split[1] {
                "cd" => match split[2] {
                    "/" => current_dir = "/".to_owned(),
                    ".." => current_dir = parent_dir(&current_dir),
                    name => current_dir = format!("{}{}/", current_dir, name),
                },
                "ls" => {}
                _ => unreachable!(),
            },
            other => match other {
                "dir" => {}
                size => {
                    let size = size.parse::<u32>().unwrap();
                    let name = split[1].to_owned();
                    let file_name = format!("{}{}", current_dir, name);
                    if let None = file_system.get(&file_name) {
                        file_system.insert(file_name, size);
                        let parent_dirs = parents(&current_dir);
                        for parent in parent_dirs {
                            let tmp_size = if let Some(dir_size) = dir_system.get(&parent) {
                                *dir_size
                            } else {
                                0
                            };
                            dir_system.insert(parent, size + tmp_size);
                        }
                    }
                }
            },
        }
    }

    let disk_size = 70000000;
    let min_space = 30000000;

    let used = *dir_system.get("/").unwrap();

    let mut min = u32::MAX;
    for (_, size) in dir_system {
        if used - size + min_space <= disk_size {
            if size < min {
                min = size;
            }
        }
    }
    println!("{}", min);
}
