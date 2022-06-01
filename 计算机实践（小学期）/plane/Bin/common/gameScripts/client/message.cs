//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

function addMessageCallback(%msgType, %func)
{
   $MSGCB[%msgType] = %func;
}

function defaultMessageCallback(%msgString)
{
   onServerMessage(detag(%msgString));
}

addMessageCallback('ClientJoined', clientJoined);
function clientJoined(%client)
{
}

addMessageCallback('ClientDropped', clientDropped);
function clientDropped(%client)
{
}

//---------------------------------------------------------------------------------------------
// ServerMessage
// Called from the server to pass a message to the client. %msgType is a message type that
// can be associated by the client with a callback
//---------------------------------------------------------------------------------------------
function clientCmdServerMessage(%msgType, %msgString)
{
   if ($MSGCB[%msgType] !$= "")
   {
      call($MSGCB[%msgType], %msgString);
      return;
   }
   
   // If nothing has handled this message yet, send it to the default callback.
   defaultMessageCallback(%msgString);
}

//---------------------------------------------------------------------------------------------
// ChatMessage
// Receives a chat message.
//---------------------------------------------------------------------------------------------
function clientCmdChatMessage(%sender, %message)
{
   onChatMessage(%sender, detag(%message));
}
