#!/usr/bin/env python
"""
Send email in Python
"""
import ConfigParser
import smtplib
import sys

def str2list(s):
    # Helper function for sendemail()
    # If input is a string, convert it to list.
    # If it is a list, keep it as is
    if type(s) is str:
        return [s]
    elif type(s) is list:
        return s
    else:
        print 'Input is neither str nor list. Something is wrong...'
        sys.exit(2)

def sendemail(to, msg_subject, msg_body, **kwargs):
    """
    Send email in Python
    Input args:
        to: destination email address(es), a string or a string list
        **kwargs, optional args: 
            cc: CC address(es), a string or a string list
            bcc: BCC address(es), a string or a string list
            profile: choose a profile in rcfile, a string; the default is 'aim'
            rcfile: the path for rcfile, a string
    Examples:
    send_email('user1@example.com', 'Test', 'This is a test')
    send_email('user1@example.com', 'Test', 'This is a test', profile='aim')
    send_email('user1@example.com', 'Test', 'This is a test', cc=['user2@example.com', 'user3@example.com'], bcc=['user3@example.com'])
    """
    profile = 'aim'
    rcfile = 'path_to_your_.sendemailrc'
    
    # You don't need to change things below
    
    # Default values
    to = str2list(to)
    cc = []
    bcc = []

    for key, val in kwargs.iteritems():
        if key == 'cc':
            cc = str2list(val)
        elif key == 'bcc':
            bcc = str2list(val)
        elif key == 'rcfile':
            if not (type(val) is str):
                print 'rcfile should be str type'
                sys.exit(2)
            else: 
                rcfile = val
        elif key == 'profile':
            if not (type(val) is str):
                print 'profile should be str type'
                sys.exit(2)
            else: 
                profile = val
        
    config = ConfigParser.ConfigParser()
    config.read(rcfile)

    if not(profile in config.sections()):
        print 'Profile not in the configuration. Exiting...'
        sys.exit(2)
    
    sender= config.get(profile, 'from')
    username = config.get(profile, 'username')
    password = config.get(profile, 'password')
    smtphost = config.get(profile, 'smtphost')
    
    msg = '\r\n'.join([
          "From: %s" % sender, 
          "To: %s" % ','.join(to),
          "CC: %s" % ','.join(cc),
          "BCC: %s" % ','.join(bcc), 
          "Subject: %s" % msg_subject,
          "",
          msg_body])
    
    #print msg
    server = smtplib.SMTP(smtphost)
    server.starttls()   # requested by gmail
    server.login(username, password)
    server.sendmail(sender, to+cc+bcc, msg)
    server.quit()
