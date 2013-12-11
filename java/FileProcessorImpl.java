import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.junit.Test;

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
