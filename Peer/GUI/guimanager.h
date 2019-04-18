#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include <QDate>
#include <QTime>

#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"
#include "GUI/friendrequestitem.h"
#include "GUI/friendrequestmodel.h"
#include "GUI/messageitem.h"
#include "GUI/messagemodel.h"

#include "dataaccessor.h"
#include "clientcontroller.h"
#include "signalredirector.h"

class GUIManager : public QObject {
  Q_OBJECT

  Q_PROPERTY(int my_id READ my_id CONSTANT)

  Q_PROPERTY(QObject* friend_model READ friend_model CONSTANT)
  Q_PROPERTY(QObject* message_model READ message_model CONSTANT)
  Q_PROPERTY(QObject* friend_request_model READ friend_request_model CONSTANT)

  Q_PROPERTY(unsigned selected_friend_id READ selected_friend_id 
             WRITE set_selected_friend_id NOTIFY SelectedFriendIdChanged)
  Q_PROPERTY(unsigned unread_requests READ unread_requests 
             WRITE set_unread_requests NOTIFY UnreadRequestsChanged)

 public:
  explicit GUIManager(QObject* parent = nullptr);
  GUIManager(const GUIManager&) = delete;
  GUIManager& operator=(const GUIManager&) = delete;

  int my_id() const;
  FriendModel* friend_model();
  MessageModel* message_model();
  FriendRequestModel* friend_request_model();

  unsigned selected_friend_id() const;
  void set_selected_friend_id(unsigned);
  unsigned unread_requests() const;
  void set_unread_requests(unsigned);


  // theese functions must start from low letter
  Q_INVOKABLE void newFriend(QString, quint32);  // temporary implementation(for testing)
  Q_INVOKABLE void newMessage(QString);
  Q_INVOKABLE void deleteFriendRiequest(FriendRequestItem*);
  void newFriendRiequest(QString login);
  void deleteFriend(quint32 id);

signals:
  void SelectedFriendIdChanged(unsigned id);
  void UnreadRequestsChanged(unsigned num);

  void openMainPage();
  void openFailed(QString text);
  void showInfo(QString text);
  void showHighlighter(bool to_show);
  void messageRing();
  void requestRing();

public slots:
  void LogIn(QString user_login, QString user_password); 
  void LogOut();
  void Register(QString user_login, QString user_password);
  void OnLoginResult(bool);
  void OnRegisterResult(quint32);
  void SendMessage(QString message);
  void ShowMessages(unsigned id);  // temporary implementation(for testing)
  void LoadAllMessages(unsigned id);
  void LoadMessage(Message* msg);
  void OnMessagesSent(unsigned);
  void OnStatusChanged(unsigned id, bool status);
  void AddFriendRequest(QString);
  void OnFriendRequestResult(bool);
  void OnAddFriendRequest(QString);
  void AcceptFriend(QString login);
  void RejectFriend(QString login);
  void OnNewFriendInfo(QString, quint32);
  void DeleteFriend(QString login);
  void OnDeleteFriend(quint32);

  // void UserEntered();

 private:
  void LoadFriendsAndMesgs();  // temporary implementation(for testing)
  unsigned selected_friend_id_;
  unsigned unread_requests_;

  FriendModel friend_model_;
  MessageModel message_model_;
  FriendRequestModel friend_request_model_;

  QMap<unsigned, QList<Message*> > messages_cache_;

 // QVector<Friend> friends_;   //FIXME: use id insted of Friend obj in sendMessage
  ClientController* controller_;
  ClientLogger* logger_;

  DataAccessor client_data_;  // for testing
};
#endif
