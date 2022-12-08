use std::collections::HashMap;

pub fn solve(input: &[String]) -> u32 {
    let mut sizes: HashMap<String, u32> = HashMap::new();

    let mut current_dir = vec![String::from("/")];
    for line in input {
        if line.starts_with("$ cd ") {
            if line == "$ cd /" {
                current_dir = vec![String::from("/")];
            } else if line == "$ cd .." {
                current_dir.pop();
            } else {
                current_dir.push(String::from(line.split(' ').into_iter().nth(2).unwrap()))
            }
        } else if let Ok(size) = line.split(' ').into_iter().next().unwrap().parse::<u32>() {
            let mut path = String::new();
            for dir in current_dir.iter() {
                path.push('/');
                path.push_str(dir);

                if !sizes.contains_key(&path) {
                    sizes.insert(path.clone(), 0);
                }

                sizes.insert(path.clone(), sizes.get(&path).unwrap() + size);
            }
        }
    }

    let to_del = 30000000 + sizes.get("//").unwrap() - 70000000;

    let mut min_d = 70000000;
    for (_, v) in sizes {
        if v >= to_del && v < min_d {
            min_d = v;
        }
    }

    min_d
}
