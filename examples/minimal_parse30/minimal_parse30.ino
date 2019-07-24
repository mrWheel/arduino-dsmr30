/*
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * Example that shows how to parse a P1 message and automatically print
 * the result.
*/

#include "dsmr30.h"

// Data to parse
const char raw[] =
    "/KMP5 KA6U001585654321\r\n"
    "\r\n"
    "0-0:96.1.1(4530303336303033373839373331234567)\r\n"
    "1-0:1.8.1(000180.670*kWh)\r\n"
    "1-0:1.8.2(000091.890*kWh)\r\n"
    "1-0:2.8.1(000117.100*kWh)\r\n"
    "1-0:2.8.2(000079.500*kWh)\r\n"
    "0-0:96.14.0(0002)\r\n"
    "1-0:1.7.0(212.33*kW)\r\n"
    "1-0:2.7.0(029.73*kW)\r\n"
    "0-0:96.13.0()\r\n"
    "0-0:96.13.1()\r\n"
    "0-1:24.1.0(3)\r\n"
    "0-1:96.1.0(4730301234567031363532303530323136)\r\n"
    "0-1:24.3.0(140101004100)(08)(60)(1)(0-1:24.2.1)(m3)\r\n"
    "(00100.006)\r\n"
    "!\r\n";

/**
 * Define the data we're interested in, as well as the datastructure to
 * hold the parsed data.
 * Each template argument below results in a field of the same name.
 */
using MyData = ParsedData<
  /* String */ identification,
  /* FixedValue */ power_delivered
>;

void setup() {
  Serial.begin(115200);

  MyData data;
  ParseResult<void> res = P1Parser::parse(&data, msg, lengthof(msg));
  if (res.err) {
    // Parsing error, show it
    Serial.println(res.fullError(msg, msg + lengthof(msg)));
  } else if (!data.all_present()) {
    Serial.println("Some fields are missing");
  } else {
    // Succesfully parsed, print results:
    Serial.println(data.identification);
    Serial.print(data.power_delivered.int_val());
    Serial.println("W");
  }
}

void loop () {
}
