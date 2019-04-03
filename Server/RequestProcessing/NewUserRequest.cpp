#pragma once
#include "NewUserRequest.h"



NewUserRequest::NewUserRequest(QByteArray& request, DAL* d, QTcpSocket* s)
    : AbstractRequest(d,s) {

	income_data_ = Parser::ParseAsRegisterInfo(request);
  QString IP = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
  QString logstring = IP + "::" + Logger::ConvertQuint16ToString(income_data_.port);
  Logger::LogOut(logstring, request);
	PrepareResponse();
}

void NewUserRequest::PrepareResponse()
{
	//Client newClient;
 //   newClient.SetUserPort(income_data_.port);
	//newClient.SetUserPassword(income_data_.password);
	//newClient.SetUserName(income_data_.login);
	//newClient.SetUserIp(client_socket_->peerAddress());
	//
	//
	//if (database_->Check_If_Client_exists_In_Db(newClient) == false) { // if client not exist
	//	database_->CreateNew(newClient);
 //       RegisterSuccessInfo register_success_info;
 //       register_success_info.id = database_->GetClientId(newClient);
 //       outcome_data_ = Parser::RegisterSuccessInfo_ToByteArray(register_success_info);		
	//	outcome_data_.append(Parser::GetUnpossibleSequence());

	//}
	//else {
	//	outcome_data_ = Parser::Empty_ToByteArray((quint8)ServerRequest::REGISTER_FAILED);
	//	outcome_data_.append(Parser::GetUnpossibleSequence());
	//}
}
bool NewUserRequest::SendResponde()
{
  QString Ip = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
  QString Logstring = Ip + "::" + Logger::ConvertQuint16ToString(income_data_.port);
  Logger::LogOut(Logstring, outcome_data_);
  
  client_socket_->write(outcome_data_);
  client_socket_->waitForBytesWritten(3000);
  client_socket_->disconnectFromHost();
	return true;
}
