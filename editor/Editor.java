import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

public class Editor extends JPanel implements MouseListener, MouseMotionListener
{
  // Constants parameters
  private static final int HPAD = 40;
  private static final int VPAD = 40;
  private static final int HSEP = 25;

  // Command-line program arguments
  private String input_source_image_name;
  private String input_target_image_name;
  private String input_correspondence_name;
  private String output_correspondence_name;
  private boolean print_verbose = false;

  // Data variables
  private BufferedImage source_image;
  private BufferedImage target_image;
  private Vector<Line2D.Double> segments = new Vector<Line2D.Double>();
  private Point current_start, current_end;

  ////////////////////////////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////////////////////////////

  public Editor(String[] args)
  {
    // Parse program arguments
    if (!parseArgs(args)) System.exit(-1);

    // Read source image
    source_image = loadImage(input_source_image_name);
    if (source_image == null) System.exit(-1);

    // Read target image
    target_image = loadImage(input_target_image_name);
    if (target_image == null) System.exit(-1);

    // Read segments
    if (input_correspondence_name != null && input_correspondence_name.length() > 0)
    {
      if (!loadCorrespondences(input_correspondence_name, source_image, target_image, segments))
        System.exit(-1);
    }

    // Calbacks
    addMouseListener(this);
    addMouseMotionListener(this);
  }

  ////////////////////////////////////////////////////////////////////////
  // Input/Output Functions
  ////////////////////////////////////////////////////////////////////////

  private static BufferedImage loadImage(String path)
  {
    BufferedImage img = null;
    if (path != null)
    {
      try { img = ImageIO.read(new File(path)); }
      catch (Exception e) {}
    }
    return img;
  }

  private boolean loadCorrespondences(String path, Image source_image, Image target_image, Vector<Line2D.Double> segments)
  {
    segments.clear();
    if (path != null)
    {
      Scanner in = null;
      try { in = new Scanner(new FileReader(path)); }
      catch (Exception e) { return false; }

      try
      {
        int num_segs = in.nextInt();
        for (int i = 0; i < num_segs; ++i)
        {
          double asx = in.nextDouble();
          double asy = in.nextDouble();
          double aex = in.nextDouble();
          double aey = in.nextDouble();

          double bsx = in.nextDouble();
          double bsy = in.nextDouble();
          double bex = in.nextDouble();
          double bey = in.nextDouble();

          segments.add(new Line2D.Double(asx, asy, aex, aey));
          segments.add(new Line2D.Double(bsx, bsy, bex, bey));
        }
      }
      catch (Exception e)
      {
        return false;
      }
    }

    return true;
  }

  private boolean saveCorrespondences(String path, Vector<Line2D.Double> segments)
  {
    PrintWriter writer;
    try
    {
      writer = new PrintWriter(output_correspondence_name, "UTF-8");
    }
    catch (IOException e)
    {
      System.err.println("Error opening file for writing");
      return false;
    }

    if (writer == null)
      return false;

    writer.println(segments.size() / 2);
    for (int i = 0; i < segments.size(); i += 2)
    {
      Line2D.Double seg1 = segments.elementAt(i);
      Line2D.Double seg2 = (i + 1 >= segments.size() ? new Line2D.Double(0.0, 0.0, 0.0, 0.0) : segments.elementAt(i + 1));

      writer.println(seg1.x1 + " " + seg1.y1 + " " + seg1.x2 + " " + seg1.y2 + " "
                   + seg2.x1 + " " + seg2.y1 + " " + seg2.x2 + " " + seg2.y2);
    }

    writer.close();
    return true;
  }

  ////////////////////////////////////////////////////////////////////////
  // Mouse handlers
  ////////////////////////////////////////////////////////////////////////

  public void mousePressed(MouseEvent e)
  {
    current_start = e.getPoint();
    current_end = null;

    if ((segments.size() % 2 == 0 && current_start.x >= source_image.getWidth())
     || (segments.size() % 2 == 1 && current_start.x < source_image.getWidth() + HSEP))
      current_start = null;
  }

  public void mouseReleased(MouseEvent e)
  {
    if (current_start != null && current_end != null)
    {
      int xoffset = (segments.size() % 2 == 1 ? source_image.getWidth() + HSEP : 0);

      segments.add(new Line2D.Double(new Point2D.Double(current_start.x - xoffset, current_start.y),
                                     new Point2D.Double(current_end.x - xoffset,   current_end.y)));
      if (segments.size() % 2 == 0)
        saveCorrespondences(output_correspondence_name, segments);
    }
    current_start = null;
  }

  public void mouseDragged(MouseEvent e)
  {
    current_end = e.getPoint();
    repaint();
  }

  public void mouseClicked(MouseEvent e) {}
  public void mouseMoved(MouseEvent e) {}
  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}

  ////////////////////////////////////////////////////////////////////////
  // Drawing
  ////////////////////////////////////////////////////////////////////////

  private void drawSegment(Line2D.Double seg, Graphics g, int xoffset)
  {
    ((Graphics2D)g).setStroke(new BasicStroke(5));
    g.drawLine((int)seg.x1 + xoffset, (int)seg.y1, (int)seg.x2 + xoffset, (int)seg.y2);
    g.fillOval((int)seg.x1 + xoffset - 5, (int)seg.y1 - 5, 11, 11);
  }

  Color getPaletteColor(int i)
  {
    final Color PALETTE[] = {
      new Color(1.0f,0.0f,0.0f), new Color(0.0f,1.0f,0.0f), new Color(0.0f,0.0f,1.0f), new Color(1.0f,0.0f,1.0f),
      new Color(0.0f,1.0f,1.0f), new Color(1.0f,1.0f,0.0f), new Color(1.0f,0.3f,0.7f), new Color(1.0f,0.7f,0.3f),
      new Color(0.7f,1.0f,0.3f), new Color(0.3f,1.0f,0.7f), new Color(0.7f,0.3f,1.0f), new Color(0.3f,0.7f,1.0f),
      new Color(1.0f,0.5f,0.5f), new Color(0.5f,1.0f,0.5f), new Color(0.5f,0.5f,1.0f), new Color(1.0f,0.5f,1.0f),
      new Color(0.5f,1.0f,1.0f), new Color(1.0f,1.0f,0.5f), new Color(0.5f,0.0f,0.0f), new Color(0.0f,0.5f,0.0f),
      new Color(0.0f,0.0f,0.5f), new Color(0.5f,0.0f,0.5f), new Color(0.0f,0.5f,0.5f), new Color(0.5f,0.5f,0.0f)
    };

    return PALETTE[i % PALETTE.length];
  }

  public void paint(Graphics g)
  {
    super.paint(g);

    int xoffset = source_image.getWidth() + HSEP;

    g.drawImage(source_image, 0, 0, null);
    g.drawImage(target_image, xoffset, 0, null);

    for (int i = 0; i < segments.size(); ++i)
    {
      g.setColor(getPaletteColor(i / 2));
      drawSegment(segments.elementAt(i), g, (i % 2 == 1 ? xoffset : 0));
    }

    if (current_start != null && current_end != null)
    {
      Line2D.Double seg = new Line2D.Double(new Point2D.Double(current_start.x, current_start.y),
                                            new Point2D.Double(current_end.x,   current_end.y));
      g.setColor(getPaletteColor(segments.size() / 2));
      drawSegment(seg, g, 0);
    }
  }

  ////////////////////////////////////////////////////////////////////////
  // Program argument parsing
  ////////////////////////////////////////////////////////////////////////

  private boolean parseArgs(String[] args)
  {
    int current_positional = 0;
    for (int i = 0; i < args.length; ++i)
    {
      if (args[i].equals("-v"))
        print_verbose = true;
      else if (args[i].equals("-input_correspondences"))
        input_correspondence_name = args[++i];
      else
      {
        switch (current_positional)
        {
          case 0: input_source_image_name = args[i]; break;
          case 1: input_target_image_name = args[i]; break;
          case 2: output_correspondence_name = args[i]; break;
          default: System.err.println("Invalid program argument: " + args[i]); return false;
        }
        current_positional++;
      }
    }

    if (input_source_image_name == null || input_target_image_name == null || output_correspondence_name == null)
      System.err.println("Usage: Editor input_source_image input_target_image output_correspondence_file"
                                    + " [-input_correspondences filename]");

    // Return OK status
    return true;
  }

  ////////////////////////////////////////////////////////////////////////
  // Main program
  ////////////////////////////////////////////////////////////////////////

  public static void main(String[] args)
  {
    // Create window
    JFrame f = new JFrame("Correspondence Editor");

    // Create a new editor
    Editor editor = new Editor(args);
    int width = editor.source_image.getWidth() + editor.target_image.getWidth();
    int height = Math.max(editor.source_image.getHeight(), editor.target_image.getHeight());
    editor.setSize(width, height);
    f.setSize(width + HPAD, height + VPAD);
    f.add(editor);

    // Run interactive interface
    f.setLocation(0, 0);
    f.setResizable(false);
    f.setVisible(true);
  }
}
