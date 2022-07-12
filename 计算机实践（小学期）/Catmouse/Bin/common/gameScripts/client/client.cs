//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// connectToServer
// Connect to a server by IP address.
//---------------------------------------------------------------------------------------------
function connectToServer(%ip)
{
   // Just in case we're already connected.
   disconnect();
   
   if(%ip $= "")
   {
      MessageBoxOK("Cannot connect to server. IP address not specified.");
      return;
   }

   %conn = new GameConnection(ServerConnection);
   %conn.setConnectArgs($pref::Player::name);
   %conn.connect(%ip);
   
   $serverConnected = true;
   $serverLocal = false;
}

//-----------------------------------------------------------------------------
// disconnect
//-----------------------------------------------------------------------------
function disconnect()
{
   if(!$serverConnected)
      return;
      
   if (isObject(ServerConnection))
      ServerConnection.delete();

   // If we were the host, make sure the server is destroyed.
   if ($serverLocal)
      destroyServer();
      
   disconnectedCleanup();
}

//-----------------------------------------------------------------------------
// disconnectedCleanup.
//-----------------------------------------------------------------------------
function disconnectedCleanup()
{
   // Clean everything up.
   alxStopAll();
   clearTextureHolds();
   purgeResources();
      
   $serverConnected = false;
   onDisconnect();
}
