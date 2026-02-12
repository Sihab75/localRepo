class student {
    int id;
    String name;
    double cgpa;
    void display () {
        System.out.print("Student Id : "+ id + "\n");
        System.out.print("Name : "+ name + "\n");
        System.out.print("Cgpa: "+ cgpa+ "\n");
    }
    public static void main (String[] args) {
        student s = new student();
        s.id = 251002084;
        s.name = "Md. Korimul Jaman";
        s.cgpa = 3.75;
        s.display();
    }
}