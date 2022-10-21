//
// Created by austi_eef6ewn on 10/20/2022.
//

#include "Database.h"

Database::Database() {
	testDatabaseClasses();
}

void Database::testDatabaseClasses() {
	Header* header;
	Tuple tuple1;
	Tuple tuple2;
	Tuple tuple3;
	Tuple tuple4;

	header = new Header();
	header->addAttribute("S");
	header->addAttribute("N");
	header->addAttribute("A");
	header->addAttribute("P");

	tuple1.addValue("12345");
	tuple1.addValue("Charlie");
	tuple1.addValue("12 Apple St.");
	tuple1.addValue("555-1234");
	tuple2.addValue("33333");
	tuple2.addValue("Snoopy");
	tuple2.addValue("12 Apple St.");
	tuple2.addValue("555-1234");
	tuple3.addValue("67890");
	tuple3.addValue("Lucy");
	tuple3.addValue("34 Pear Ave.");
	tuple3.addValue("555-5678");

	Relation relation("snap", header);
	relation.addTuple(tuple1);
	relation.addTuple(tuple2);
	relation.addTuple(tuple3);
	relation.toString();

	delete header;
}