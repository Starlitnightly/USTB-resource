function initChat(%name)
{
      $chatStarted = true;
	if(%name $= "")
		%name = "Torque Game Builder Chat";
      new SimSet(chatGroup);
	chatGroup.name = %name;
}

function onClientConnected(%client)
{
   
}

function onServerCreated()
{
   
}

function onServerDestroyed()
{

}

function getConnectionList(%client)
{
   $serverConnectionList = "";
   $serverNameList = "";
   $serverConnectionCount = 0;

   %connectionCount = ClientGroup.getCount();

   %count = 0;
   for(%i=0;%i<%connectionCount;%i++)
   {
	%connection = ClientGroup.getObject(%i);
      %name = %connection.name;

      $serverConnectionList = $serverConnectionList @ %connection;
      $serverConnectionList = $serverConnectionList @ "|";

      $serverNameList = $serverNameList @ %name;
      $serverNameList = $serverNameList @ "|";

      %count++;
   }

   $serverConnectionCount = %count;

   commandToClient(%client, 'passConnectionCount', $serverConnectionCount);
   commandToClient(%client, 'passConnectionList', $serverConnectionList);
   commandToClient(%client, 'passNameList', $serverNameList);
}

function getChatConnectionList(%client)
{
   $serverChatConnectionList = "";
   $serverChatNameList = "";
   $serverChatConnectionCount = 0;

   %chatCount = ChatGroup.getCount();

   %count = 0;
   for(%i=0;%i<%chatCount;%i++)
   {
	%chat = chatGroup.getObject(%i);
      %name = %chat.name;
      
      $serverChatConnectionList = $serverChatConnectionList @ %chat;
      $serverChatConnectionList = $serverChatConnectionList @ "|";

      $serverChatNameList = $serverChatNameList @ %name;
      $serverChatNameList = $serverChatNameList @ "|";

      %count++;
   }

   $serverChatConnectionCount = %count;

   commandToClient(%client, 'passChatConnectionCount', $serverChatConnectionCount);
   commandToClient(%client, 'passChatConnectionList', $serverChatConnectionList);
   commandToClient(%client, 'passChatNameList', $serverChatNameList);
}

function serverCmdGetConnectionList(%client)
{
   getConnectionList(%client);
}

function serverCmdGetChatConnectionList(%client)
{
   getChatConnectionList(%client);
}

function serverCmdisChatting(%client)
{
   chatGroup.add(%client);
   updateChatClient(%client.name);
}

function serverCmdleftChat(%client)
{
   chatGroup.remove(%client);
   removeChatClient(%client.name);
}

function serverCmdupdateChatText(%client, %text)
{
   updateChatText(%client.name, %text);
}

function updateChatText(%clientName, %text)
{
   %count = chatGroup.getCount();

   for(%i=0;%i<%count;%i++)	
   {
      %client = chatGroup.getObject(%i);
      commandToClient(%client, 'updateChatText', %clientName, %text);      
   }
}

function updateChatClient(%clientName)
{
   %count = chatGroup.getCount();

   for(%i=0;%i<%count;%i++)
   {
      %client = chatGroup.getObject(%i);
      commandToClient(%client, 'updateChatClient', %clientName);      
   }
}

function removeChatClient(%clientName)
{
   %count = chatGroup.getCount();

   for(%i=0;%i<%count;%i++)
   {
      %client = chatGroup.getObject(%i);
      commandToClient(%client, 'removeChatClient', %clientName);      
   }
}

function onClientDropped(%client)
{  
   if($chatStarted && isObject(ChatGroup))
   { 
      ChatGroup.remove(%client);
      removeChatClient(%client.name);
   }
}

function sendChatLoaded()
{
   $ServerChatLoaded = true;
}

function serverCmdisChatLoaded(%client)
{
   commandToClient(%client, 'isChatLoaded', $ServerChatLoaded);
}

function sendChatClosed(%clientName)
{
   %count = chatGroup.getCount();

   for(%i=0;%i<%count;%i++)
   {
      %client = chatGroup.getObject(%i);
      commandToClient(%client, 'chatClosed');      
   }

   chatGroup.clear();
}