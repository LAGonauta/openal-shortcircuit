(Get-FileHash -Algorithm SHA1 .\OpenAL.dll).Hash.ToLower() > OpenAL.dll.sha1
