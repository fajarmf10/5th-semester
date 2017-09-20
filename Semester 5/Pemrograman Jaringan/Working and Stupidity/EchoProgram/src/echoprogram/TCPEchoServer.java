/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package echoprogram;

import java.io.*;
import java.net.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 *
 * @author fajar
 */
public class TCPEchoServer {

    /**
     * @param args the command line arguments
     */
    
    private static ServerSocket serverSocket;
    private static final int PORT = 8228;
    private static int i = 0;
    private static URL lala;

    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("Opening port…\n");
        try{
            serverSocket = new ServerSocket(PORT); //Step 1.
        }
        catch(IOException ioEx){
            System.out.println("Unable to attach to port!");
            System.exit(1);
        }
        do{
            handleClient();
        }while(true);
    }
    
    private static void handleClient(){
        Socket link = null; //Step 2
        try{
            link = serverSocket.accept(); //Step 2
//            Scanner input2 = new Scanner(link.getInputStream());
            Scanner input = new Scanner(link.getInputStream()); //Step 3
            PrintWriter output = new PrintWriter(link.getOutputStream(), true); //Step 3.
//            PrintWriter output2 = new PrintWriter(link.getOutputStream(), true);
            int numMessages = 0;
            BufferedReader br = null;
            String id[][] = new String[1000][5];
            String message = input.nextLine(); //Step 4.
//            DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
            DateFormat jam = new SimpleDateFormat("hh:mm:ss");
            DateFormat hari = new SimpleDateFormat("EEEE");
            DateFormat bulan = new SimpleDateFormat("MM");
            Date now = new Date();// EEE gives short day names, EEEE would be full length.
            
            //br = new BufferedReader(new FileReader("E:\\college\\Semester 5\\Pemrograman Jaringan\\Working and Stupidity\\EchoProgram\\src\\echoprogram\\id.txt"));
            //String contentLine = br.readLine();
//            while(i < 186){
//                //5115100001-Fajar Maulana Firdaus
//                id[i] = contentLine.split("-");
//                contentLine = br.readLine();
//                i++;
//            }
            
            while (!message.equals("!q")){
                switch (message) {
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
                message = input.nextLine();
                }
            output.println(numMessages + " messages received."); //Step 4.
        }
        catch(IOException ioEx){
            ioEx.printStackTrace();
        }
        finally{
            try{
                System.out.println("\n* Closing connection… *");
                link.close(); //Step 5.
            }
            catch(IOException ioEx){
                System.out.println("Unable to disconnect!");
                System.exit(1);
            }
        }
    }
}
