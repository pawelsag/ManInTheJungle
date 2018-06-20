import struct
import os
pathToLevel = "C:\SDLPRojects\SDL GAME\config\\" 

def decodeLevel(readFileName, writeFileName):
	k=[]
	with open( pathToLevel + readFileName , "rb") as f:
		k =  f.read()
		
		with open( pathToLevel + writeFileName , "wb") as f2:
			x = [ i for i in reversed(k[15:19]) ]
			f2.write( bytearray(x) ) # write x-size
			y = [ i for i in reversed(k[19:23]) ]
			f2.write( bytearray(y) ) # write y-size
			# unpack offset to long int 
			dataOffset = struct.unpack( "<L", k[10:14] )[0]
			# read data from bmp file without header
			k = k[dataOffset::]
			
			# read evry third byte
			k = k[0+2 ::3]
			# reverse map
			k = reversed(k)
			f2.write( bytearray(k) )

def findBmpFiles():
	for file in os.listdir(pathToLevel):
		if(file[-3::] == "bmp" ):
			dstName = file.replace("bmp","bin")
			decodeLevel(file,dstName)		
			

if __name__ == "__main__":
	findBmpFiles()
