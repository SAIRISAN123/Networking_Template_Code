using System;
using UnityEngine;
using MikeSchweitzer.WebSocket;
using System.Collections.Generic;


public class WebSocketClient : MonoBehaviour
{

    public WebSocketConnection _connection;


    public class Message
    {
        public string a;
        public int[] b;
        public List<int[]> c;
        public int d;
        public string e;
    }     // defined message structure



    // URL of the WebSocket server
    public string _url = "ws://localhost:8765";


    private void Awake()
    {
        if (_connection == null)
        {
            _connection = gameObject.AddComponent<WebSocketConnection>();
        }

        // Set up event listeners
        _connection.MessageReceived += OnMessageReceived;
        _connection.ErrorMessageReceived += OnErrorMessageReceived;
        _connection.StateChanged += OnStateChanged;

        // Configure and connect
        ConnectToServer();
    }

    private void OnDestroy()
    {
        _connection.MessageReceived -= OnMessageReceived;
        _connection.ErrorMessageReceived -= OnErrorMessageReceived;
        _connection.StateChanged -= OnStateChanged;

        DisconnectFromServer();
    }

    private void ConnectToServer()
    {
        // Configure WebSocket
        _connection.DesiredConfig = new WebSocketConfig
        {
            Url = _url,
            PingInterval = TimeSpan.FromSeconds(3),
            PingMessage = new WebSocketMessage("ping")
        };

        // Connect to the WebSocket server
        _connection.Connect();
        Debug.Log("Connecting to WebSocket server...");
    }

    private void DisconnectFromServer()
    {
        // Disconnect from the WebSocket server
        _connection.Disconnect();
        Debug.Log("Disconnected from WebSocket server.");
    }


    private void OnMessageReceived(WebSocketConnection connection, WebSocketMessage message)
    {
        Debug.Log($"Message received: {message.String}");        // print message to console
                                                                 // MSGTest = JsonUtility.FromJson<AGVMessage>(message.String);   // string to json .... must assign initially

    }



    private void OnErrorMessageReceived(WebSocketConnection connection, string errorMessage)
    {
        //Debug.LogError($"WebSocket error: {errorMessage}");
    }

    private void OnStateChanged(WebSocketConnection connection, WebSocketState oldState, WebSocketState newState)
    {
        //Debug.Log($"WebSocket state changed from {oldState} to {newState}");
    }


    public void SendMessageToServer(string message)    // send message to server
    {
        if (_connection.State == WebSocketState.Connected)
        {
            _connection.AddOutgoingMessage(message);
            Debug.Log($"Message sent: {message}");
        }
        else
        {
            Debug.LogWarning("Cannot send message. WebSocket is not connected.");
        }
    }
}