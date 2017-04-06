#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "../header/library.h"

using namespace std;

int main()
{
	
	MotorBody driveData;
	driveData.direction = FORWARD;
	driveData.duration = 5;
	
	//Create and configure PktDef test
	PktDef sendPkt;
	sendPkt.setPktCount(1);
	sendPkt.setCmd(SLEEP);
	sendPkt.setBodyData(reinterpret_cast<char*>(&driveData), 2);
	
	sendPkt.calcCRC();

	//Create buffer to hold data
	char* buffer = sendPkt.genPacket();

	PktDef recvPkt(buffer);

	recvPkt.calcCRC();

	std::cout << "PktCount: " << recvPkt.getPktCount() << '\n';
	std::cout << "Pkt Length: " << recvPkt.getLength() << '\n';
	std::cout << "Ack status: " << recvPkt.getAck() << '\n';
	std::cout << "Cmd received: " << recvPkt.getCmd() << '\n';
	std::cout << "CRC Check status: " << recvPkt.checkCRC(buffer, 8) << '\n';

	char* ptr = recvPkt.getBodyData();
	//CRC check test code
	//Note: CRC check covers HEADER and DATA only. 
	//So it will be length of the struct - 1 byte for CRC data
	//std::cout << "testRec pkt checkCRC() result: " 
		//<< testRecv.checkCRC(buffer, test.cmdPacket.header.length - 1) << std::endl;;

	//==== Professor's test code below ====

	//MotorBody DriveCmd;
	//DriveCmd.direction = FORWARD;
	//DriveCmd.duration = 20;

	//PktDef TestPkt;
	//char *ptr;

	////Testing the PktDef creation interface
	//TestPkt.setCmd(DRIVE);
	//TestPkt.setBodyData((char *)&DriveCmd, 2);
	//TestPkt.setPktCount(1);
	//TestPkt.calcCRC();
	//ptr = TestPkt.genPacket();

	//cout << showbase
	//	<< internal
	//	<< setfill('0');

	//for (int x = 0; x < (int)TestPkt.getLength(); x++)
	//	cout << hex << setw(4) << (unsigned int)*(ptr++) << ", ";

	//cout << endl;
	//TestPkt.setCmd(ACK);
	//TestPkt.calcCRC();
	//ptr = TestPkt.genPacket();

	//for (int x = 0; x < (int)TestPkt.getLength(); x++)
	//	cout << hex << setw(4) << (unsigned int)*(ptr++) << ", ";

	//cout << endl << noshowbase << dec;
	////Testing Rx Buffer interface
	////You should create RAW data packets (like below) to test your overloaded constructor
	//char buffer[9] = { 0x02, 0x00, 0x00, 0x00, 0x02, 0x09, 0x11, 0x24, 0x08};
	//PktDef RxPkt(buffer);
	//cout << "CommandID:  " << RxPkt.getCmd() << endl;
	//cout << "PktCount:   " << RxPkt.getPktCount() << endl;
	//cout << "Pkt Length: " << RxPkt.getLength() << endl;
	//cout << "Body Data: " << endl;

	//ptr = RxPkt.getBodyData();
	//cout << showbase << hex;
	//cout << "Byte 1 " << (int)*ptr++ << endl;
	//cout << "Byte 2 " << (int)*ptr << endl;

	//return 1;
}
