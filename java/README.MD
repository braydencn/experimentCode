# Line Processor implementation in Java

Someone asked a question in forum. He need to open files, 
read and process one line at a time. As the processing
logic are different, the code become longer and more ugly. 

We could introduce Strategy pattern to solve this:
    public interface FileProcessor {
        void processByLine(String FilePath, LineProcessor processor);
    }
    
    public interface LineProcessor {
        void doSomeThing(String oneLine);
    }

    public class FileProcessorImpl implements FileProcessor {
    
        @Override
        public void processByLine(String filePath, LineProcessor processor) {
            try (BufferedReader br =
                    new BufferedReader(new FileReader(filePath))) {
                    String line = br.readLine();
                    processor.doSomeThing(line.trim());
            }catch (FileNotFoundException fnfe){
                fnfe.printStackTrace();
            }catch (IOException ioe){
                ioe.printStackTrace();
            }
        }
    }
    
In client code, do:
    new FileProcessorImpl().processByLine("a.txt", new LineProcessor(){
        @Override
        public void doSomeThing(String oneLine) {
            // business logic
        }
    });
