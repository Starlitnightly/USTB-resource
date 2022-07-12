function onConnect()
{
   if(waitingForServer.isAwake())
      canvas.popDialog(waitingForServer);

   MessageBoxOK("Connection Established...", "Connection Established with the server!", "");
}

//--------------------------------------------------
// callbacks for getting a connection/name list of all clients
//--------------------------------------------------
function clientCmdPassConnectionList(%connectionList)
{
	$clientConnectionsList = new ScriptObject(clientConnectionsList);
	
	%list = explode(%connectionList, "|");
	%count = $clientConnectionCount;
	
	for(%i=0;%i<%count;%i++)
	{
		$clientConnectionsList.contents[%i] = %list.contents[%i];
	}	
}

function clientCmdPassNameList(%nameList)
{
	$clientNamesList = new ScriptObject(clientNamesList);
	
	%list = explode(%nameList, "|");
	%count = $clientConnectionCount;
	for(%i=0;%i<%count;%i++)
	{
		$clientNamesList.contents[%i] = %list.contents[%i];
	}	
}

function clientCmdPassConnectionCount(%connectionCount)
{
	$clientConnectionCount = %connectionCount;
}


//----------------------------------------------------

function clientCmdPassChatConnectionList(%connectionList)
{
	$clientChatConnectionsList = new ScriptObject(clientChatConnectionsList);
	
	%list = explode(%connectionList, "|");
	%count = $clientChatConnectionCount;
	for(%i=0;%i<%count;%i++)
	{
		$clientChatConnectionsList.contents[%i] = %list.contents[%i];
	}	
}

function clientCmdPassChatNameList(%nameList)
{
	$clientChatNamesList = new ScriptObject(clientChatNamesList);
	
	%list = explode(%nameList, "|");
	%count = $clientChatConnectionCount;
	for(%i=0;%i<%count;%i++)
	{
		$clientChatNamesList.contents[%i] = %list.contents[%i];
	}	

   if($waitingForList)
   {
      chatGui::onGetList();
   }
}

function clientCmdPassChatConnectionCount(%connectionCount)
{
	$clientChatConnectionCount = %connectionCount;
}
//----------------------------------------------------




function clientCmdupdateChatText(%clientName, %text)
{
   %string = %clientName @ ": " @ %text;
   chatVectorText.pushBackLine(%string, 0);
}


function clientCmdupdateChatClient(%clientName)
{
   if(!isObject(clientChatInfo))
      new SimSet(clientChatInfo);

   if(clientChatInfo.clientCount $= "")
      clientChatInfo.clientCount = 0;

  // clientChatInfo.add(%clientName);
   chatClientList.addRow(clientChatInfo.clientCount, %clientName);
   $chat::clientCount++;
}

function clientCmdremoveChatClient(%clientName)
{
   clientChatInfo.remove(%clientName);
   chatClientList.removeRow(chatClientList.findTextIndex(%clientName));
   $chat::clientCount--;
}

function loadChat()
{
   if($serverConnected)
   {
      if($serverLocal)
      {
         //First lets start the chat system
         initChat();

         //This is called if the server is initiating a chat, lets load it
         Canvas.pushDialog(chatGui);

         //Now we send messaged out to the clients saying that the server has established a chat
         sendChatLoaded();
      } else
      {
         commandToServer('isChatLoaded');
         canvas.pushDialog(waitingForServer);
      }
   } else
   {
      MessageBoxOK("Loading Chat...", "Loading chat failed: No Server Connection Exists.", "");
   }
}



function clientCmdisChatLoaded(%isChatLoaded)
{
   if(waitingForServer.isAwake())
      canvas.popDialog(waitingForServer);
   //This is called if you are not the server and are trying to connect to the chat
   if(%isChatLoaded)
   {
      //If the chat is loaded then you open the gui
      mainScreenGui.add(chatGui);
      
   } else
   {
      //If the chat isn't loaded we send an error box
      MessageBoxOK("Loading Chat...", "Loading chat failed: No Chat Loaded on Server.", "");
   }
}

function clientCmdChatClosed()
{
   serverData.chatLoaded = false;

   if(!$serverLocal)
   {
      if(chatGui.isAwake())
      {
         mainScreenGui.remove(chatGui);
      }
   }
}




function explode(%string, %char)
{
	if(!isObject(explode))
		new ScriptObject(explode);

	%explodeCount = 0;
	%lastFound = 0;

	%endChar = strLen(%string);	
	%charLen = strLen(%char);

	for(%i=0;%i<%endChar;%i++)
	{
		%charToCheck = getSubStr(%string, %i, %charLen);
		if(%charToCheck $= %char)
		{
			explode.contents[%explodeCount] = getSubStr(%string, %lastFound, (%i-%lastFound)); 
			%lastFound = %i + %charLen;
			%explodeCount++;
		}	
	}

	
	explode.contents[%explodeCount] = getSubStr(%string, %lastFound, (%i-%lastFound)); 
	explode.count = %explodeCount + 1;	

	return explode;
}

