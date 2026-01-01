/*
 * 2026.1.2
 * fizzbuzz.rs
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


const EG: &str = "./fizzbuzz -f 3 -b 5 -n 15";


fn main()
{
	let args = std::env::args();
	println!("{:?}", args);

	let args_vec: Vec<String> = args.collect();
	println!("{:?}", args_vec);	


	let mut f = 3; let mut b = 5; let mut fb = 3*5;
	let mut m = 15; // 100, 150
	for i in 0..args_vec.len()
	{
		if &args_vec[i][..1] == "-" && args_vec[i+1].parse::<u64>().is_ok()
		{
			match &args_vec[i][1..2]
			{
				"n" => m = args_vec[i+1].parse().unwrap(),
				"f" => f = args_vec[i+1].parse().unwrap(),
				"b" => b = args_vec[i+1].parse().unwrap(),
				&_ => println!("No option {}", args_vec[i]),
			}
			if f*b != 0 { fb = f*b; }
			if m == 0 { m = fb; }
		}
		else
		{
			if i == 0 { println!("for example command : {}", EG); }
		}
	}
	println!();


	let mut n = 0;
	while n < m
	{
		n += 1;
		if n % fb == 0 { println!("FizzBuzz"); }
		else if n % f == 0 { println!("Fizz"); }
		else if n % b == 0 { println!("Buzz"); }
		else { println!("{}", n); }
	}
}