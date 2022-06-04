class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        eset = set()
        for email in emails:
            name, domain = email.split('@')
            name = name.split('+')[0].replace('.', '')
            eset.add(name + '@' + domain)
        return len(eset)