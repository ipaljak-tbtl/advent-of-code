use std::collections::HashMap;
//use std::collections::HashSet;

pub fn solve(input: &[String]) -> u32 {
    let mut sizes: HashMap<String, u32> = HashMap::new();
    //let mut added_files: HashSet<String> = HashSet::new();

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
            //let fname = line.split(' ').into_iter().skip(1).next().unwrap();
            let mut path = String::new();
            for dir in current_dir.iter() {
                /* if !added_files.insert(current_dir.join("/") + "/" + fname) {
                    continue;
                } */

                path.push('/');
                path.push_str(dir);

                if !sizes.contains_key(&path) {
                    sizes.insert(path.clone(), 0);
                }

                sizes.insert(path.clone(), sizes.get(&path).unwrap() + size);
            }
        }
    }

    let mut cnt = 0;
    for (_, v) in sizes {
        if v <= 100000 {
            cnt += v;
        }
    }

    cnt
}
