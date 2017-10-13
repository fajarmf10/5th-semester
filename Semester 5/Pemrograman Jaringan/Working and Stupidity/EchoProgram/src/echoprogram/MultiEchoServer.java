/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

/**
 *
 * @author sosispanggang
 */
public class MultiEchoServer {

    private static ServerSocket serverSocket;
    private static final int PORT = 1234;

    public static void main(String[] args)
            throws IOException {
        try {
            serverSocket = new ServerSocket(PORT);
        } catch (IOException ioEx) {
            System.out.println("\nUnable to set up port!");
            System.exit(1);
        }
        do {
//Wait for client...
            Socket client = serverSocket.accept();
            System.out.println("\nNew client accepted.\n");
//Create a thread to handle communication with
//this client and pass the constructor for this
//thread a reference to the relevant socket...
            ClientHandler handler
                    = new ClientHandler(client);
            handler.start();//As usual, method calls run .
        } while (true);
    }
}

class ClientHandler extends Thread {

    private Socket client;
    private Scanner input;
    private PrintWriter output;

    public ClientHandler(Socket socket) {
//Set up reference to associated socket...
        client = socket;
        try {
            input = new Scanner(client.getInputStream());
            output = new PrintWriter(
                    client.getOutputStream(), true);
        } catch (IOException ioEx) {
            ioEx.printStackTrace();
        }
    }

    public void run() {
        String received;
        do {
//Accept message from client on
//the socket's input stream...
            received = input.nextLine();
//Echo message back to client on
//the socket's output stream...
            output.println("Command used: " + received);
//Repeat above until 'QUIT' sent by client...
        } while (!received.equals("QUIT"));
        try {
            int numMessages = 0;
            DateFormat jam = new SimpleDateFormat("hh:mm:ss");
            DateFormat hari = new SimpleDateFormat("EEEE");
            DateFormat bulan = new SimpleDateFormat("MM");
            Date now = new Date();// EEE gives short day names, EEEE would be full length.
            switch (received) {
                    case "!t":
                        //Jam
                        System.out.println("Client getting the time.");
                        output.println("Jam :" + jam.format(now));
                        output.flush();
                        break;
                    case "!d":
                        System.out.println("Client want to know the current day.");
                        output.println(hari.format(now));
                        output.flush();
                        break;
                    case "!m":
                        System.out.println("Client want to know the current month.");
                        output.println(bulan.format(now));
                        output.flush();
                        break;
                    case "!#":
                        System.out.println("Client searching for quote, hehe.");
                        output.println("The best love is the kind that awakens the soul; that makes us reach for more, that plants the fire in our hearts and brings peace to our minds. That's what I hope to give you forever.");
                        output.flush();
                        break;
                    case "!id":
                        Scanner serverEntry = new Scanner(System.in);
                        String serverinput;
                        
//                    System.out.print("Enter message to client: ");
//                    serverinput = serverEntry.nextLine();
//                    output.println("Server says: " + serverinput);
//                    System.out.println("Client want to get the ID.");
//                    output.flush();
//                    message = input.nextLine();
//                    for(i=0; i<id.length; i++){
//                        if(id[i][0].equals(message)){
//                            output2.println("Name is:" + id[i][1]);
//                        }
//                        else {
//                            output2.println("Nothing found :(");
//                        }
//                    }
                        break;
                    default:
                        System.out.println("Message received.");
                        numMessages++;
                        output.println("Your #" + numMessages + " message(s) is: " + message); //Step 4.
                        break;
                }


            if (client != null) {
                System.out.println(
                        "Closing down connection...");
                client.close();
            }
        } catch (IOException ioEx) {
            System.out.println("Unable to disconnect!");
        }
    }
}
