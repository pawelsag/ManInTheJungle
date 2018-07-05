import struct
import os
pathToLevel = "C:\SDLPRojects\SDL GAME\config\\" 
pathToLevelProcess = "C:\SDLPRojects\SDL GAME\config\levels\\" 
def decodeLevel(readFileName, writeFileName):
	k=[]

	with open( pathToLevel + readFileName , "rb") as f:
		k =  f.read()
		
		with open( pathToLevelProcess + writeFileName , "wb") as f2:
			x = [ i for i in reversed(k[15:19]) ]
			cols = struct.unpack(">L", k[15:19])
			f2.write( bytearray(x) ) # write x-size
			y = [ i for i in reversed(k[19:23]) ]
			rows = struct.unpack(">L", k[19:23])
			f2.write( bytearray(y) ) # write y-size
			# unpack offset to long int 
			dataOffset = struct.unpack( "<L", k[10:14] )[0]
			# read data from bmp file without header
			k = k[dataOffset::]
			
			# read evry third byte
			k = k[0+2 ::3]
			# count all diffrent signs
			countSigns(k, f2)
			# reverse map

			k = reversed(k)
			
			k = reverseColumns(k, rows, cols)
			# print(list(k))
			f2.write( bytearray(k) )

def countSigns(byteTable, fileDescriptor):
	signs ={}
	counter = 0
	for sign in byteTable:
		if(sign in signs):
			signs[sign] +=1
		else:
			signs.update({sign : 1})
	# data offset for data 
	 							# x_size ,y_size ,dataOffset_size signDescription_size
	# print(len(signs))  
	dataOffset = struct.pack("<H", (4 + 4 + 2 + len(signs) )  )
	fileDescriptor.write(dataOffset)
	for key,value in signs.items():
		fileDescriptor.write(struct.pack("<B", key ) )
		
def reverseColumns(map, rows, cols):
	map = list(map)

	for i in range( cols[0]//2 ):
		temp = map[i::200]
		map[i::200] = map[(cols[0]-i-1)::200]
		map[(cols[0]-i-1)::200] = temp 
	
			
	return map




def findBmpFiles():
	for file in os.listdir(pathToLevel):
		if(file[-3::] == "bmp" ):
			dstName = file.replace("bmp","bin")
			decodeLevel(file,dstName)		
			

if __name__ == "__main__":
	findBmpFiles()
