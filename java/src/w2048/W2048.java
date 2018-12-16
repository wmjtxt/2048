package w2048;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.util.*;

import javax.swing.*;

@SuppressWarnings("serial")
public class W2048 extends JFrame {
    // �ƶ�����
    final public static int MOVE_UP = 0xf37;
    final public static int MOVE_DOWN = 0xf36;
    final public static int MOVE_LEFT = 0xf35;
    final public static int MOVE_RIGHT = 0xf34;
    // ��Ϸ״̬
    final public static int GAME_OVER = 0xf33;
    final public static int GAME_CONTINUE = 0xf32;
    final public static int GAME_WIN = 0xf31;
    // ��ť�¼�
    final public static int BUTTON_NEW_GAME = 0xf30;
    final public static int BUTTON_ABOUT = 0xf28;
    final public static int BUTTON_EXIT = 0xf27;

    /**
     * ��
     */
    private int column;
    /**
     * ��
     */
    private int row;
    /**
     * ��Ϸ״̬
     */
    private int gameState;
    /**
     * ����
     */
    private HashMap<Point, Cube> viewList = new HashMap<>();
    /**
     * �Ʒְ�
     */
    private JMenuItem scoreBoard;
    /**
     * �Ʋ���
     */
    private JMenuItem arithmometer;
    /**
     * �Ʋ�
     */
    private int count;
    /**
     * ����Ϸ������
     */
    private int gameLv;

    /**
     * main����
     * 
     * @param args
     */
    public static void main(String[] args) {
        W2048 game = new W2048(400, 500);
        game.setTitle("2048");
        game.setLocationRelativeTo(null);
        game.setVisible(true);
        game.newGame();
    }

    /**
     * ����һ��Ĭ�ϴ�С�Ľ���
     */
    public W2048() {
        this(400, 500);
    }

    /**
     * ����һ��ָ����ߵĽ���
     * 
     * @param width
     *            ��
     * @param height
     *            ��
     */
    public W2048(int width, int height) {
        column = width / 100;
        row = height / 100;

        this.setLayout(new GridLayout(row, column));
        // �¼�����
        enableEvents(AWTEvent.WINDOW_EVENT_MASK);
        this.setSize(width, height);

        // ����button ��������
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                viewList.put(new Point(i, j), new Cube());
                this.add(getView(i, j).getView());
            }
        }

        // ���ð�������
        this.addKeyListener(new MyKeyListener(this));

        JMenuBar jmb = new JMenuBar();
        JMenu jm = new JMenu("��Ϸ");
        JMenuItem item1 = new JMenuItem("����Ϸ");
        item1.addMouseListener(new MyMouseListener(this,
                W2048.BUTTON_NEW_GAME));
        JMenuItem item2 = new JMenuItem("�˳�");
        item2.addMouseListener(new MyMouseListener(this, W2048.BUTTON_EXIT));
        jm.add(item1);
        jm.add(item2);

        JMenu jm2 = new JMenu("����");
        JMenuItem item3 = new JMenuItem("����");
        item3.addMouseListener(new MyMouseListener(this, W2048.BUTTON_ABOUT));
        jm2.add(item3);

        scoreBoard = new JMenuItem();
        arithmometer = new JMenuItem();

        jmb.add(jm);
        jmb.add(jm2);
        jmb.add(scoreBoard);
        jmb.add(arithmometer);
        this.setJMenuBar(jmb);
    }

    /**
     * �����ƶ�
     */
    public void up() {
        for (int x = 1; x < row; x++) {
            for (int i = 0; i < column; i++) {
                move(W2048.MOVE_UP, x, i, true);
            }
        }

        createCube();
        for (int x = 1; x < row; x++) {
            for (int i = 0; i < column; i++) {
                move(W2048.MOVE_UP, x, i, false);
            }
        }
        addCount();
    }

    /**
     * �����ƶ�
     */
    public void down() {
        for (int x = row - 2; x >= 0; x--) {
            for (int y = 0; y < column; y++) {
                move(W2048.MOVE_DOWN, x, y, true);
            }
        }

        createCube();
        for (int x = row - 2; x >= 0; x--) {
            for (int y = 0; y < column; y++) {
                move(W2048.MOVE_DOWN, x, y, false);
            }
        }

        addCount();
    }

    /**
     * �����ƶ�
     */
    public void left() {
        for (int y = 1; y < column; y++) {
            for (int x = 0; x < row; x++) {
                move(W2048.MOVE_LEFT, x, y, true);
            }
        }

        createCube();
        for (int y = 1; y < column; y++) {
            for (int x = 0; x < row; x++) {
                move(W2048.MOVE_LEFT, x, y, false);
            }
        }

        addCount();
    }

    /**
     * �����ƶ�
     */
    public void right() {
        for (int y = column - 2; y >= 0; y--) {
            for (int x = 0; x < row; x++) {
                move(W2048.MOVE_RIGHT, x, y, true);
            }
        }

        createCube();
        for (int y = column - 2; y >= 0; y--) {
            for (int x = 0; x < row; x++) {
                move(W2048.MOVE_RIGHT, x, y, false);
            }
        }

        addCount();
    }

    /**
     * �ƶ�
     * 
     * @param move_way
     *            �ƶ�����
     * @param x
     *            ������
     * @param y
     *            ������
     */
    private void move(int move_way, int x, int y, boolean isAdd) {
        switch (move_way) {
        case W2048.MOVE_DOWN: {
            for (; x < row - 1; x++) {
                swap(getView(x + 1, y), getView(x, y), isAdd);
            }
        }
            break;

        case W2048.MOVE_LEFT: {
            for (; y > 0; y--) {
                swap(getView(x, y - 1), getView(x, y), isAdd);
            }
        }
            break;

        case W2048.MOVE_RIGHT: {
            for (; y < column - 1; y++) {
                swap(getView(x, y + 1), getView(x, y), isAdd);
            }
        }
            break;

        case W2048.MOVE_UP: {
            for (; x > 0; x--) {
                swap(getView(x - 1, y), getView(x, y), isAdd);
            }
        }
            break;
        }
    }

    /**
     * ���򽻻�ʵ���ƶ�
     * 
     * @param next
     *            �ƶ���Ŀ��λ��
     * @param now
     *            ��Ҫ�ƶ���Ŀ��
     * @param isAdd
     *            �Ƿ��ǵ�һ���ƶ�
     */
    private void swap(Cube next, Cube now, boolean isAdd) {
        if (isAdd) {
            if (now.getNum() != 0 && next.getNum() == 0) {
                next.setText(now.getNum());
                now.setText(0);
                next.setIsAdded(now.isAdded());
                now.setIsAdded(false);
            } else if (!now.isAdded() && !next.isAdded()
                    && next.getNum() == now.getNum() && now.getNum() != 0) {
                next.setText(now.getNum() * 2);
                now.setText(0);
                next.setIsAdded(true);
                now.setIsAdded(false);
            }
        } else {
            if (next.getNum() == 0) {
                next.setText(now.getNum());
                now.setText(0);
            }
            now.setIsAdded(false);
            next.setIsAdded(false);
        }
    }

    /**
     * ��ȡָ���ؼ�
     * 
     * @param x
     * @param y
     * @return Cube
     */
    private Cube getView(int x, int y) {
        return viewList.get(new Point(x, y));
    }

    /**
     * ��������ؼ� ���λ��
     */
    private void createCube() {
        int x;
        int y;

        do {
            x = (int) (Math.random() * 1000 % row);
            y = (int) (Math.random() * 1000 % column);
        } while (getView(x, y).getNum() != 0);

        getView(x, y).setText(Math.random() > 0.5 ? 2 : 4);
        isOverGame();
    }

    /**
     * �����Ϸ״̬
     */
    private void isOverGame() {
        int score = 0;
        int state = W2048.GAME_OVER;

        for (int x = 0; x < row; x++) {
            for (int y = 0; y < column; y++) {

                // ����÷�
                score += getView(x, y).getNum();

                if (getView(x, y).getNum() == 0) {
                    state = W2048.GAME_CONTINUE;
                } else if (getView(x, y).getNum() == 2048 * (gameLv + 1)) {
                    state = W2048.GAME_WIN;
                }
            }
        }

        if (state != W2048.GAME_CONTINUE && state != W2048.GAME_WIN) {
            gameState = W2048.GAME_OVER;
        } else {
            gameState = state;
        }

        scoreBoard.setText("�÷�:" + score);

    }

    /**
     * �Ʋ�
     */
    private void addCount() {
        count++;
        arithmometer.setText("�Ʋ���" + count);
    }

    /**
     * ��ȡ��Ϸ״̬
     * 
     * @return int
     */
    public int getGameState() {
        return gameState;
    }

    /**
     * ��ʼ����Ϸ����
     */
    private void initialise() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                getView(i, j).setText(0);
            }
        }

        createCube();
        createCube();
        count = 0;
        arithmometer.setText("�Ʋ���" + count);
        gameLv = 0;
        this.setTitle("2048");
    }

    /**
     * ��������Ϸ
     */
    public void newGame() {
        if (gameState == W2048.GAME_CONTINUE) {
            int jop = JOptionPane.showConfirmDialog(null, "�Ƿ�ʼ��һ����Ϸ?", "Tips",
                    JOptionPane.YES_NO_OPTION);

            if (jop == JOptionPane.YES_OPTION) {
                initialise();
            }
        } else {
            initialise();
        }
    }

    /**
     * ���ش����¼�-���ƹر�
     */
    protected void processWindowEvent(WindowEvent e) {
        if (e.getID() == WindowEvent.WINDOW_CLOSING) {
            if (getGameState() == W2048.GAME_CONTINUE) {
                int jop = JOptionPane.showConfirmDialog(null, "�Ƿ��˳���Ϸ?",
                        "Tips", JOptionPane.YES_NO_OPTION);

                if (jop == JOptionPane.YES_OPTION) {
                    super.processWindowEvent(e);
                }
            } else {
                super.processWindowEvent(e);
            }
        }
    }

    /**
     * ������һ�Ѷ���Ϸ
     */
    public void nextLv() {
        gameLv++;
        this.setTitle(2048 * (gameLv + 1) + "");
    }

    /**
     * ����
     */
    public void about() {
        JOptionPane.showMessageDialog(null, "E-mail:czh60601@126.com");
    }
}

class Cube {
    private int num;
    private JButton btn;
    private boolean isAdded;

    /**
     * ����һ������
     */
    public Cube() {
        btn = new JButton();
        btn.setFont(new Font("΢���ź�", Font.BOLD, 24));
        btn.setEnabled(false);
        num = 0;
        isAdded = false;
    }

    /**
     * �����ı�����
     * 
     * @param n
     *            ��ֵ
     */
    public void setText(int n) {
        num = n;
        btn.setText(n != 0 ? n + "" : "");
    }

    /**
     * ��ȡ�ؼ�
     * 
     * @return JButton
     */
    public JButton getView() {
        return btn;
    }

    /**
     * ��ȡ��ֵ
     * 
     * @return int
     */
    public int getNum() {
        return num;
    }

    /**
     * �Ƿ�����Ӷ��� �޵�ǰ�ƶ�����Ч,�ƶ�������Ļ�Ĭ��ֵ-false
     * 
     * @return
     */
    public boolean isAdded() {
        return isAdded;
    }

    /**
     * �޸����ɷ�ʽ
     * 
     * @param b
     *            true-��Ӷ���
     */
    public void setIsAdded(boolean b) {
        isAdded = b;
    }

}

class MyKeyListener implements KeyListener {
    /*
     * ���̴��� w/87 s/83 a/65 d/68 up/38 down/40 left/37 right/39 f1/112 f2/113
     * f3/114
     */
    final public static int KEY_W = 0xf57;
    final public static int KEY_S = 0xf53;
    final public static int KEY_A = 0xf41;
    final public static int KEY_D = 0xf44;
    final public static int KEY_UP = 0xf26;
    final public static int KEY_DOWN = 0xf28;
    final public static int KEY_LEFT = 0xf25;
    final public static int KEY_RIGHT = 0xf27;

    private W2048 game;

    /**
     * ����һ�����̼�����
     * 
     * @param game
     *            ������
     */
    public MyKeyListener(W2048 game) {
        this.game = game;
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode() + 0xf00;

        switch (game.getGameState()) {
        case W2048.GAME_CONTINUE: {
            switch (keyCode) {
            case MyKeyListener.KEY_W:
            case MyKeyListener.KEY_UP: {
                game.up();
            }
                break;

            case MyKeyListener.KEY_S:
            case MyKeyListener.KEY_DOWN: {
                game.down();
            }
                break;

            case MyKeyListener.KEY_A:
            case MyKeyListener.KEY_LEFT: {
                game.left();
            }
                break;

            case MyKeyListener.KEY_D:
            case MyKeyListener.KEY_RIGHT: {
                game.right();
            }
                break;
            }
        }
            break;

        case W2048.GAME_OVER: {
            int jop = JOptionPane
                    .showConfirmDialog(null, "���ź�����û�ܴ�ɱ���Ŀ�꣬�Ƿ�������Ϸ?", "��Ϸ����",
                            JOptionPane.YES_NO_OPTION);

            if (jop == JOptionPane.YES_OPTION) {
                game.newGame();
            }
        }
            break;

        case W2048.GAME_WIN: {
            int jop = JOptionPane.showConfirmDialog(null,
                    "������ɱ���Ŀ��:" + game.getTitle() + ",�Ƿ��������Ѷ���Ϸ?", "��ϲ����",
                    JOptionPane.YES_NO_OPTION);

            if (jop == JOptionPane.YES_OPTION) {
                game.nextLv();
            }
        }
            break;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }

    @Override
    public void keyTyped(KeyEvent e) {

    }
}

class MyMouseListener implements MouseListener {
    private W2048 game;
    private int btnEvn;

    public MyMouseListener(W2048 game, int btnEvn) {
        this.game = game;
        this.btnEvn = btnEvn;
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {
        switch (btnEvn) {
        case W2048.BUTTON_NEW_GAME: {
            game.newGame();
        }
            break;

        case W2048.BUTTON_ABOUT: {
            game.about();
        }
            break;

        case W2048.BUTTON_EXIT: {
            game.processWindowEvent(new WindowEvent(game,
                    WindowEvent.WINDOW_CLOSING));
        }
            break;
        }
    }

}