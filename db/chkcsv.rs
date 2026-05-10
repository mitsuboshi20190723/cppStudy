/*
 * 2026.5.10
 * chkcsv.rs
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

use std::fs;


fn option_analysis(args: std::env::Args) -> (String, Vec<String>)
{
	let args_vec: Vec<String> = args.collect();
	let d: String = args_vec[1].clone();

	let fnls = fs::read_dir(&d).unwrap();
	
	for fname in fnls
	{
		if true
		{
			println!("{:?}", fname.unwrap().file_name());
		}
	}

	return (d, args_vec);
}


fn main()
{
	let (d, lsfn) = option_analysis(std::env::args());


	print!("{} ", d);
	println!(" : {:?}", lsfn);
}