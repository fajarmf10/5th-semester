import java.io.DataInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import static MultiThreadChatServer.groups;

/**
 *
 * @author ayya
 */
public class MultiThreadChatServer {

  // The server socket.
  private static ServerSocket serverSocket = null;
  // The client socket.
  private static Socket clientSocket = null;

  // This chat server can accept up to maxClientsCount clients' connections.
  private static final int maxClientsCount = 10;
  private static final clientThread[] threads = new clientThread[maxClientsCount];
  
  public static final Map<String,List<clientThread>> groups=new HashMap<>(); //string nama grup, list daftar membernya 
  
  public static void main(String args[]) {

    // The default port number.
    int portNumber = 2222;
    if (args.length < 1) {
      System.out
          .println("Usage: java MultiThreadChatServer <portNumber>\n"
              + "Now using port number=" + portNumber);
    } else {
      portNumber = Integer.valueOf(args[0]).intValue();
    }

    /*
     * Open a server socket on the portNumber (default 2222). Note that we can
     * not choose a port less than 1023 if we are not privileged users (root).
     */
    try {
      serverSocket = new ServerSocket(portNumber);
    } catch (IOException e) {
      System.out.println(e);
    }

    /*
     * Create a client socket for each connection and pass it to a new client
     * thread.
     */
    while (true) {
      try {
        clientSocket = serverSocket.accept();
        int i = 0;
        for (i = 0; i < maxClientsCount; i++) {
          if (threads[i] == null) {
            (threads[i] = new clientThread(clientSocket, threads)).start();
            break;
          }
        }
        if (i == maxClientsCount) {
          PrintStream os = new PrintStream(clientSocket.getOutputStream());
          os.println("Server too busy. Try later.");
          os.close();
          clientSocket.close();
        }
      } catch (IOException e) {
        System.out.println(e);
      }
    }
  }
}
/*
 * The chat client thread. This client thread opens the input and the output
 * streams for a particular client, ask the client's name, informs all the
 * clients connected to the server about the fact that a new client has joined
 * the chat room, and as long as it receive data, echos that data back to all
 * other clients. When a client leaves the chat room this thread informs also
 * all the clients about that and terminates.
 */
class clientThread extends Thread {

  private DataInputStream is = null;
  private PrintStream os = null;
  private Socket clientSocket = null;
  private final clientThread[] threads;
  private int maxClientsCount;
  private String username; //tambahan
  
  public clientThread(Socket clientSocket, clientThread[] threads) {
    this.clientSocket = clientSocket;
    this.threads = threads;
    maxClientsCount = threads.length;
  }

  public void run() {
    int maxClientsCount = this.maxClientsCount;
    clientThread[] threads = this.threads;

    try {
      /*
       * Create input and output streams for this client.
       */
      is = new DataInputStream(clientSocket.getInputStream());
      os = new PrintStream(clientSocket.getOutputStream());
      os.println("Enter your name.");
      String name = is.readLine().trim();
      username = name; //tambahan
      os.println("Hello " + name
          + " to our chat room.\nTo leave enter /quit in a new line");
      for (int i = 0; i < maxClientsCount; i++) {
        if (threads[i] != null && threads[i] != this) {
          threads[i].os.println("*** A new user " + name
              + " entered the chat room !!! ***");
        }
      }
      while (true) {
        String line = is.readLine();
        if (line.startsWith("/quit")) {
          break;
        }
        else if (line.startsWith("@")) //tambahan
        {
            String array[] = line.split("[@ ]",3);
            String username, message;
            username = array[1];
            message = array[2];
            for (clientThread client : threads)
            {
                if(client.username.equals(username))
                {
                    client.os.println("<" + name + "--> " + message);
                }
            }
        }
        else if (line.startsWith("create#"))
        {
            String array[]=line.split("#");
            String group;
            group = array[1];
            if (groups.containsKey(group))
            {
                os.println("Grup sudah ada, silahkan cari nama lain !!!");
            }
            else 
            {
                groups.put(group, new ArrayList<>());
                groups.get(group).add(this);
                os.println("Welcome to " + group);
            } 
        }
        else if (line.startsWith("join#"))
        {
            String array[]=line.split("#");
            String group;
            group = array[1];
            if (groups.containsKey(group))
            {
                if (groups.get(group).contains(this))
                {
                    os.println("gblk");
                }
                else 
                {
                    groups.get(group).add(this);
                    os.println("Selamat anda telah masuk grup "+group);
                }
            }
            else
            {
                os.println("Grup yang anda inginkan tidak ada");
            }
        }
        else if (line.startsWith("chat#"))
        {
            String array[]=line.split("[# ]",3);
            String group,message;
            group = array[1];
            message = array[2];
            if (groups.containsKey(group))
            {
                if (groups.get(group).contains(this))
                {
                    for (clientThread client : groups.get(group))
                    {
                        if(!client.username.equals(username))
                        {
                            client.os.println("<" + name + " " + group + "--> " + message);
                        }
                    }
                }
            }
            else
            {
                os.println("Anda belum bergabung dalam grup/ grup tidak ada");
            }
            
        }
        else 
        {
            for (int i = 0; i < maxClientsCount; i++) {
                if (threads[i] != null) {
                threads[i].os.println("<" + name + "--> " + line);
                }
            }
        }
      }
      for (int i = 0; i < maxClientsCount; i++) {
        if (threads[i] != null && threads[i] != this) {
          threads[i].os.println("*** The user " + name
              + " is leaving the chat room !!! ***");
        }
      }
      os.println("*** Bye " + name + " ***");

      /*
       * Clean up. Set the current thread variable to null so that a new client
       * could be accepted by the server.
       */
      for (int i = 0; i < maxClientsCount; i++) {
        if (threads[i] == this) {
          threads[i] = null;
        }
      }

      /*
       * Close the output stream, close the input stream, close the socket.
       */
      is.close();
      os.close();
      clientSocket.close();
    } catch (IOException e) {
    }
  }
}