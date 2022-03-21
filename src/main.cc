/*
 * main.cc
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * mountain is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * mountain is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>


#include "Database.hh"

int main()
{
	oct::mont::Database db("tests/DB");
	
	
	std::cout << "version : " << db.get_version().toString() << std::endl;
	
	std::cout << "name : " << db.get_name() << std::endl;
	
	
	return 0;
}

